/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:35:52 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/27 16:33:26 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_triple(char ***cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
		clear(cmds[i], size_double(cmds[i]));
	free(cmds);
}

void	clear(char **paths, int j)
{
	while (--j >= 0)
		free(paths[j]);
	free(paths);
}
