/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:56:17 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 06:49:05 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(int *i)
{
	int	j;

	j = skip_space(g_global.line, *i);
	if ((g_global.line[j] == '|' && j != *i + 1) || !g_global.line[j])
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	else if (g_global.line[*i + 1] == '|' && g_global.line[*i + 2] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	*i = j - 1;
	return (1);
}

int	check_and(int *i)
{
	int	j;

	j = skip_space(g_global.line, *i);
	j = skip_space(g_global.line, *i + 1);
	if (g_global.line[*i + 1] != '&' || !g_global.line[j])
	{
		write(2, "minishell: syntax error\n", 24);
		return (0);
	}
	else if (g_global.line[*i + 2] == '&' || g_global.line[j] == '&')
	{
		write(2, "minishell: syntax error\n", 24);
		return (0);
	}
	*i = j - 1;
	return (1);
}

int	check_red(int *i)
{
	int	j;

	j = skip_space(g_global.line, *i);
	if (g_global.line[*i] + g_global.line[j] == 122 && \
	abs(g_global.line[*i] - g_global.line[j]) == 2)
		return (!write(2, "minishell: syntax error\n", 24));
	else if ((g_global.line[*i] == g_global.line[j] && \
	j != *i + 1) || !g_global.line[j])
		return (!write(2, "minishell: syntax error\n", 24));
	else if (g_global.line[*i + 1] == g_global.line[*i] && \
	g_global.line[*i + 2] == g_global.line[*i])
		return (!write(2, "minishell: syntax error\n", 24));
	else if (g_global.line[j] == '|')
		return (!write(2, "minishell: syntax error \
		near unexpected token `|'\n", 50));
	*i = j - 1;
	return (1);
}

int	check_error(void)
{
	int	i;

	i = -1;
	g_global.line = unclosed_quotes();
	if (!g_global.line)
		return (0);
	g_global.line = unclosed_brackets();
	if (!g_global.line)
		return (0);
	while (g_global.line[++i])
	{
		i = skip_quotes(g_global.line, i, g_global.line[i]);
		if (g_global.line[i] == '|' && !check_pipe(&i))
			return (0);
		else if (g_global.line[i] == '&' && !check_and(&i))
			return (0);
		else if ((g_global.line[i] == '<' || g_global.line[i] == '>')
			&& !check_red(&i))
			return (0);
	}
	return (1);
}
