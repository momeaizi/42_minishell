/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 10:26:40 by mskerba           #+#    #+#             */
/*   Updated: 2022/09/06 11:50:55 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*join_readline_with_line(char *line)
{
	char	*buf;
	char	*new_line;

	buf = readline(">");
	if (!buf)
	{
		free(line);
		return (NULL);
	}
	new_line = ft_strjoin(line, "\n");
	free(line);
	line = ft_strjoin(new_line, buf);
	free(new_line);
	free(buf);
	return (line);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_global.doc_exit = 1;
		g_global.exit_code = 1;
		g_global.fd = dup(0);
		close(0);
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (!g_global.doc_exit)
			write(1, "\n", 1);
		g_global.exit_code = 1;
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}
