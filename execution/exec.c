/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:23:09 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/06 14:49:19 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_cmds(char *command, t_cmd *cmd)
{
	if (cmd->error || !cmd->args[0])
		return ;
	if (!ft_strcmp("echo", command))
		ft_echo(cmd);
	else if (!ft_strcmp("cd", command))
	{
		change_env_var("OLDPWD", getcwd(NULL, 0));
		ft_cd(cmd);
		change_env_var("PWD", getcwd(NULL, 0));
	}
	else if (!ft_strcmp("pwd", command))
		ft_pwd(cmd);
	else if (!ft_strcmp("export", command))
		ft_export(cmd);
	else if (!ft_strcmp("unset", command))
		ft_unset(cmd);
	else if (!ft_strcmp("env", command))
		ft_env(cmd);
	else if (!ft_strcmp("exit", command))
		ft_exit(cmd);
	else if (!cmd->path)
		cmd->path = get_path(cmd, cmd->args[0]);
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

void	waiting_childs(int *pid)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = g_global.cmds;
	while (tmp)
	{
		waitpid(pid[i++], &g_global.exit_code, 0);
		if (g_global.exit_code == 2 || g_global.exit_code == 3)
			g_global.exit_code += 128;
		else
			g_global.exit_code = WEXITSTATUS(g_global.exit_code);
		tmp = tmp->next;
	}
	free(pid);
}

void	child(t_cmd *tmp, int pid)
{
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		check_cmds(tmp->args[0], tmp);
		if (!tmp->error && tmp->path)
		{
			dup2(tmp->in, 0);
			dup2(tmp->out, 1);
			close_all(g_global.cmds);
			execve(tmp->path, tmp->args, g_global.env);
			put_error(tmp->args[0], strerror(errno));
			exit(errno);
		}
		exit(tmp->error);
	}
}

void	exec(t_cmd *tmp, int *pid, int i)
{
	pid = malloc(list_size(tmp) * sizeof(int));
	if (!tmp->next)
	{
		check_cmds(tmp->args[0], tmp);
		g_global.exit_code = tmp->error;
		if (!tmp->path)
		{
			free(pid);
			return ;
		}
	}
	signal(SIGINT, SIG_IGN);
	while (tmp)
	{
		pid[i++] = fork();
		child(tmp, pid[i - 1]);
		if (tmp->in != 0)
			close(tmp->in);
		if (tmp->out != 1)
			close(tmp->out);
		tmp = tmp->next;
	}
	waiting_childs(pid);
}
