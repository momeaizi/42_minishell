/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:34:22 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/03 09:39:58 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
}

void	clear_all(t_token ***tokens)
{
	clear_tokens(tokens);
	clear_cmds();
	free(g_global.line);
}

void	init_prompt(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	g_global.line = readline("minishell> ");
	g_global.doc_exit = 0;
	if (!g_global.line)
	{
		write(1, "exit\n", 5);
		exit(g_global.exit_code);
	}
	remove_tab(g_global.line);
}

void	minishell(int flag, t_token ***tokens)
{
	while (1)
	{
		init_prompt();
		if (ft_strlen(g_global.line))
			add_history(g_global.line);
		if (!ft_strlen(g_global.line) || is_space(g_global.line))
		{
			free(g_global.line);
			continue ;
		}
		flag = check_error();
		if (g_global.doc_exit)
			dup2(g_global.fd, 0);
		if (!flag)
		{
			free(g_global.line);
			continue ;
		}
		g_global.line = add_spaces(g_global.line);
		tokens = lexer(g_global.line);
		parser(tokens);
		if (!g_global.doc_exit)
			exec(g_global.cmds, NULL, 0);
		clear_all(tokens);
	}
}

int	main(int ac, char **av, char **env)
{
	t_token	***tokens;
	int		flag;

	flag = 1;
	tokens = NULL;
	if (ac != 1 && av[1])
		return (1);
	g_global.env = copy_env(env);
	g_global.exit_code = 0;
	minishell(flag, tokens);
	return (0);
}
