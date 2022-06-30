/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:16:43 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 06:48:22 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_cmd *cmd)
{
	if (!cmd->args[2])
	{
		write(2, "exit\nbash: exit: ", 17);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else if (ft_atoi(cmd->args[1]) >= INT_MAX
		|| ft_atoi(cmd->args[1]) <= INT_MIN)
	{
		write(2, "exit\nbash: exit: ", 17);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(ft_atoi(cmd->args[1]));
	}
	else
		exit(ft_atoi(cmd->args[1]));
	return (1);
}
