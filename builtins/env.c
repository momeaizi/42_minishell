/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:16:19 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 12:00:52 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->args[1])
		return (1);
	while (g_global.env[++i])
	{
		if (ft_strchr(g_global.env[i], '='))
		{
			write(cmd->out, g_global.env[i], ft_strlen(g_global.env[i]));
			write(cmd->out, "\n", 1);
		}
	}
	return (1);
}
