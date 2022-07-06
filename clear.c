/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:14:06 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/05 23:55:59 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_tokens(t_token ***tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j])
		{
			free(tokens[i][j]->token);
			free(tokens[i][j]);
		}
		free(tokens[i]);
	}
	free(tokens);
}

void	clear_cmds(void)
{
	t_cmd	*current;
	int		i;

	current = g_global.cmds;
	while (g_global.cmds)
	{
		i = -1;
		current = g_global.cmds;
		g_global.cmds = g_global.cmds->next;
		if (current->path)
			free(current->path);
		while (current->args[++i])
			free(current->args[i]);
		free(current->args);
		free(current);
	}
}

void	close_all(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->in != 0)
			close(cmd->in);
		if (cmd->out != 1)
			close(cmd->out);
		cmd = cmd->next;
	}
}
