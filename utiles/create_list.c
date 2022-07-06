/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:43:56 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/06 14:49:56 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i);
}

void	create_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	node->in = 0;
	node->out = 1;
	node->path = NULL;
	node->error = 0;
	node->doc_index = 0;
	node->args = ft_calloc(1, sizeof(char *));
	node->next = NULL;
	if (g_global.cmds)
		node->next = g_global.cmds;
	g_global.cmds = node;
}

int	open_pipes(void)
{
	int		pipes[2];
	t_cmd	*tmp;

	tmp = g_global.cmds;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		if (pipe(pipes) < 0)
			return (0);
		tmp->out = pipes[1];
		tmp->next->in = pipes[0];
		tmp = tmp->next;
	}
	return (1);
}

void	create_list(int size)
{
	g_global.cmds = NULL;
	while (size--)
		create_node();
	open_pipes();
}
