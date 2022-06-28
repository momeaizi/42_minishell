/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:43:06 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 17:01:26 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_double(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		;
	return (i);
}

/*void	open_heredocs(t_token ***tokens)
{
	int	j;
	int	i;

	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
			if (!tokens[i][j]->type)
				read_from_heredoc(tokens[i][j]->type);
		g_global.cmds = g_global.cmds->next;
	}
}*/

void	parser(t_token ***tokens)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	tmp = g_global.cmds;
	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			if (!tokens[i][j]->type)
				tmp->args = ft_realloc(tmp->args, tokens[i][j]->token);
			else if (tokens[i][j]->type == 1)
				open_infile(tmp, tokens[i][j]->token);
			else if (tokens[i][j]->type == 2)
				open_outfile(tmp, tokens[i][j]->token, 0);
			else if (tokens[i][j]->type == 3)
				open_outfile(tmp, tokens[i][j]->token, 1);
		}
		tmp = tmp->next;
	}
}

int	is_redirection(char *token)
{
	if (!ft_strcmp("<", token))
		return (1);
	else if (!ft_strcmp(">", token))
		return (2);
	else if (!ft_strcmp(">>", token))
		return (3);
	else if (!ft_strcmp("<<", token))
		return (4);
	return (0);
}

void	specify_type(t_token ***tokens)
{
	int	i;
	int	j;
	int	type;

	i = -1;
	while (tokens[++i])
	{
		j = 0;
		if (!is_redirection(tokens[i][j]->token))
			tokens[i][j]->type = is_redirection(tokens[i][j]->token);
		while (tokens[i][++j])
		{
			type = is_redirection(tokens[i][j - 1]->token);
			if (!is_redirection(tokens[i][j]->token))
				tokens[i][j]->type = type;
		}
	}
}

t_token	***tokenizer(char ***sub_cmds, int size)
{
	t_token	***tokens;
	int		i;
	int		j;

	i = -1;
	tokens = (t_token ***)ft_calloc(sizeof(t_token **), size + 1);
	while (sub_cmds[++i])
	{
		tokens[i] = (t_token **)ft_calloc(sizeof(t_token *),
				size_double(sub_cmds[i]) + 1);
		j = -1;
		while (sub_cmds[i][++j])
		{
			tokens[i][j] = (t_token *)malloc(sizeof(t_token));
			tokens[i][j]->token = ft_strdup(sub_cmds[i][j]);
			tokens[i][j]->type = -1;
		}
	}
	return (tokens);
}

t_cmd	*lexer(char *line)
{
	int		size;
	t_token	***tokens;
	char	**cmds;
	char	***sub_cmds;
	int		i;

	i = -1;
	split(&cmds, line, '|');
	size = size_double(cmds);
	sub_cmds = (char ***)ft_calloc(sizeof(char **), size + 1);
	while (cmds[++i])
		split(&sub_cmds[i], cmds[i], ' ');
	tokens = tokenizer(sub_cmds, size);
	specify_type(tokens);
	create_list(size);
	parser(tokens);
	clear(cmds, size);
	clear_triple(sub_cmds);
	return (NULL);
}
