/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:02:59 by mskerba           #+#    #+#             */
/*   Updated: 2022/09/19 20:48:20 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_line(char *line)
{
	char	*new_line;
	int		len;

	len = -1;
	while (line[++len] && line[len] == ' ')
		;
	line = line + len;
	len = skip_brackets(line, 0) - 1;
	while (line[++len] && line[len] != '&' && line[len] != '|')
		;
	new_line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	new_line[len] = 0;
	while (--len >= 0)
		new_line[len] = line[len];
	return (new_line);
}

char	*extract_line(char *line, int type)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		i = skip_quotes(line, i, line[i]);
		i = skip_brackets(line,i);
		if (type == 1 && line[i] == '&')
		{
			free(line);
			return (ft_strdup(line + i + 2));
		}
		if (type == 2 && line[i] == '|') 
		{
			free(line);
			return (ft_strdup(line + i + 2));
		}
	}
	return (NULL);
}

int	is_and_or(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		i = skip_quotes(line, i, line[i]);
		i = skip_brackets(line,i);
		if (line[i] == '&' && line[i + 1] == '&')
			return (1);
		if (line[i] == '|' && line[i + 1] == '|')
			return (2);
	}
	return (0);
}

void	new_minishell(char *line, t_token ***tokens)
{
	char	*new_line;
	int		status;
	char	*tmp;
	int		pid;
	
	while(1)
	{
		
		tmp = ft_strtrim(line, " ");
		free(line);
		line = tmp;
		if(line[0] == '(' && line[ft_strlen(line) - 1] == ')')
		{
			line[ft_strlen(line) - 1] = 0;
			pid = fork();
			if (!pid)
			{
				new_minishell(ft_strdup(line + 1),tokens);
				exit(g_global.exit_code);
			}
			waitpid(pid, &g_global.exit_code, 0);
			break;
		}
		status = is_and_or(line);
		if (status)
		{
			new_line = is_line(line);
			new_minishell(new_line, tokens);
			line = extract_line(line, status);
			if (status == 1 && g_global.exit_code == 0)
				continue;
			else if (status == 2 && g_global.exit_code != 0)
				continue;
			else
				break;
		}
		tokens = lexer(line);
		parser(tokens);
		if (!g_global.doc_exit)
			exec(g_global.cmds, NULL, 0);
		clear_all(tokens);
		break;
	}
	free(line);
}
