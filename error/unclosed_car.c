/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_car.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:31:18 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/20 21:58:19 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*unclosed_quotes(void)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (g_global.line[++i] && !g_global.doc_exit)
	{
		j = skip_quotes(g_global.line, i, g_global.line[i]);
		if (!g_global.line[j] && !g_global.doc_exit)
		{
			g_global.line = join_readline_with_line(g_global.line);
			if (g_global.doc_exit)
				return (g_global.line);
			else if (!g_global.line)
			{
				write(2, "\nminishell: syntax error: unexpected end of file\n",
					49);
				break ;
			}
			i--;
			continue ;
		}
		i = j;
	}
	return (g_global.line);
}

static void	continue_check(int *num_of_brack)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (g_global.line[++i])
	{
		i = skip_quotes(g_global.line, i, g_global.line[i]);
		j = skip_space(g_global.line, i);
		if ((g_global.line[i] == ')' && !(*num_of_brack)) || (g_global.line[i]
				== '(' && g_global.line[j] == ')'))
		{
			write(2, "minishell: syntax error near unexpected token `)'\n", 50);
			break ;
		}
		else if (g_global.line[i] == '(')
			(*num_of_brack)++;
		else if (g_global.line[i] == ')')
			(*num_of_brack)--;
	}
}

char	*unclosed_brackets(void)
{
	int		num_of_brack;
	char	*new_line;

	num_of_brack = 0;
	continue_check(&num_of_brack);
	if (num_of_brack)
	{
		g_global.line = join_readline_with_line(g_global.line);
		g_global.line = unclosed_quotes();
		new_line = unclosed_brackets();
		free(g_global.line);
		return (new_line);
	}
	return (g_global.line);
}

int	valid_parentheses(char *line)
{
	int	i;
	int	j;

	i = -1;
	while (line[++i])
	{
		i = skip_quotes(line, i, line[i]);
		j  = skip_space(line, i);
		if (line[j] == '(' && i && line[i] != '&' && line[i] != '|')
		{
			write(2, "minishell: syntax error\n", 24);
			return (0);
		}
		if (line[i] == ')' && line[j] && line[j] != '&' && line[j] != '|')
		{
			write(2, "minishell: syntax error\n", 24);
			return (0);
		}
		i  = j - 1;
	}
	return (1);
}