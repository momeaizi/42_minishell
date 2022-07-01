/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:34:22 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 22:25:00 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	check_cmds(char *command, t_cmd *cmd)
{
	if (cmd->error)
		return (0);
	if (!ft_strcmp("echo", command))
		return (ft_echo(cmd));
	else if (!ft_strcmp("cd", command))
		return (ft_cd(cmd));
	else if (!ft_strcmp("pwd", command))
		return (ft_pwd(cmd));
	else if (!ft_strcmp("export", command))
		return (ft_export(cmd));
	else if (!ft_strcmp("unset", command))
		return (ft_unset(cmd));
	else if (!ft_strcmp("env", command))
		return (ft_env(cmd));
	else if (!ft_strcmp("exit", command))
		return (ft_exit(cmd));
	else if (!cmd->path)
	{
		cmd->error = 127;
		put_error(cmd->args[0], "command not found");
	}
	return (0);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	new_env = (char **)ft_calloc((size_double(env) + 1), sizeof(char *));
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	return (new_env);
}

void	exec(void)
{
	int		id;
	t_cmd	*tmp;

	tmp = g_global.cmds;
	while (tmp)
	{
		if (check_cmds(tmp->args[0], tmp))
			return ;
		id = fork();
		if (!id)
		{
			if (!tmp->error && tmp->path)
			{
				dup2(tmp->in, 0);
				dup2(tmp->out, 1);
				if (tmp->in != 0)
					close(tmp->in);
				if (tmp->out != 1)
					close(tmp->out);
				execve(tmp->path, tmp->args, g_global.env);
				put_error(tmp->args[0], strerror(errno));
				exit(errno);
			}
			exit(tmp->error);
		}
		if (tmp->in != 0)
			close(tmp->in);
		if (tmp->out != 1)
			close(tmp->out);
		wait(&g_global.error);
		g_global.error = WEXITSTATUS(g_global.error);
		tmp = tmp->next;
	}
}

int	is_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_token	***tokens;

	ac = 4;
	av = NULL;
	g_global.env = copy_env(env);
	signal(SIGINT, sig_handler);
	while (1)
	{
		g_global.line = readline("minishell> ");
		g_global.error = 0;
		g_global.doc_exit = 0;
		if (!g_global.line)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (!ft_strlen(g_global.line) || is_space(g_global.line))
		{
			free(g_global.line);
			continue ;
		}
		add_history(g_global.line);
		if (!check_error())
			continue ;
		g_global.line = add_spaces(g_global.line);
		tokens = lexer(g_global.line);
		parser(tokens);
		exec();
		clear_tokens(tokens);
		clear_cmds();
		free(g_global.line);
		// system("leaks minishell");
	}
}

void	clear_tokens(t_token ***tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			free(tokens[i][j]->token);
			free(tokens[i][j]);
		}
		free(tokens[i]);
	}
	free(tokens);
}

void	clear_cmds(void)
{
	t_cmd	*current;
	int		i;

	current = g_global.cmds;
	while (g_global.cmds)
	{
		i = -1;
		current = g_global.cmds;
		g_global.cmds = g_global.cmds->next;
		if (current->path)
			free(current->path);
		while (current->args[++i])
			free(current->args[i]);
		free(current->args);
		free(current);
	}
}
