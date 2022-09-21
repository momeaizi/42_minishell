/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:02:59 by mskerba           #+#    #+#             */
/*   Updated: 2022/09/21 11:18:48 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char *line)
{
	char	*new_line;
	int		len;

	len = skip_brackets(line, 0);
	while (line[++len] && line[len] != '&' \
	&& !(line[len] == '|' && line[len + 1] == '|'))
		;
	new_line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	new_line[len] = 0;
	while (--len >= 0)
		new_line[len] = line[len];
	return (new_line);
}

char	*get_next_cmd(char *line)
{
	char	*new_line;
	char	c;
	int		i;

	i = -1;
	c = '|';
	if (g_global.exit_code == 0)
		c = '&';
	while (line[++i])
	{
		i = skip_quotes(line, i, line[i]);
		i = skip_brackets(line, i);
		if (line[i] == c && line[i + 1] == c)
		{
			new_line = ft_strdup(line + i + 2);
			free(line);
			return (new_line);
		}
	}
	return (NULL);
}

int	is_operator(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		i = skip_quotes(line, i, line[i]);
		i = skip_brackets(line, i);
		if (line[i] == '&' && line[i + 1] == '&')
			return (1);
		if (line[i] == '|' && line[i + 1] == '|')
			return (2);
	}
	return (0);
}

int	fork_for_parenthesis(char *line, t_token ****tokens)
{
	int	pid;

	if (line[0] == '(' && (int)ft_strlen(line) == skip_brackets(line, 0))
	{
		line[ft_strlen(line) - 1] = 0;
		pid = fork();
		if (!pid)
		{
			parse_execute(ft_strdup(line + 1), *tokens);
			exit(g_global.exit_code);
		}
		waitpid(pid, &g_global.exit_code, 0);
		g_global.exit_code = WEXITSTATUS(g_global.exit_code);
		return (1);
	}
	return (0);
}

void	parse_execute(char *line, t_token ***tokens)
{
	char	*new_line;

	while (1)
	{
		line = ft_strtrim(line, " ");
		if (fork_for_parenthesis(line, &tokens))
			break ;
		if (is_operator(line))
		{
			new_line = get_cmd(line);
			parse_execute(new_line, tokens);
			line = get_next_cmd(line);
			if (!line)
				return ;
			continue ;
		}
		tokens = lexer(line);
		parser(tokens);
		if (!g_global.doc_exit)
			exec(g_global.cmds, NULL, 0);
		clear_all(tokens);
		break ;
	}
	free(line);
}
