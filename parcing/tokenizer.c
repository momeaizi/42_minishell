/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:43:06 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/06 14:49:31 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_token	***lexer(char *line)
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
	clear(cmds, size);
	clear_triple(sub_cmds);
	return (tokens);
}
