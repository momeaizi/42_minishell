/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:34:22 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/29 08:43:15 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("minishell> ", 0);
		rl_redisplay();
	}
}

int	main()
{
	while (1)
	{
		signal(SIGINT, sig_handler);
		g_global.line = readline("minishell> ");
		g_global.doc_exit= 0;
		if (!g_global.line)
		{
			write(1, "exit\n", 5);
			exit (0);
		}
		if (!ft_strlen(g_global.line))
			continue ;
		add_history(g_global.line);
		if (!check_error())
			continue ;
		g_global.line = add_spaces(g_global.line);
		lexer(g_global.line);
		free(g_global.line);
	}
}
		// system("leaks minishell");
