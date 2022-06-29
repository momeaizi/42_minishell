/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:24:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 18:37:21 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		while (tokens[i][++j] && !tmp->error)
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
