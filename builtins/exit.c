/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:16:43 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/02 12:37:15 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_args_exit(char *args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (ft_isdigit(args[i]) || (!i && args[i] == '-'))
			continue ;
		return (0);
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	if (!cmd->args[1])
		exit(0);
	else if (check_args_exit(cmd->args[1]) && ft_strlen(cmd->args[1]) < 19)
		exit((unsigned char)ft_atoi(cmd->args[1]));
	else
	{
		write(2, "exit\n", 5);
		put_error_two("exit", cmd->args[1], "numeric argument required");
		exit(255);
	}
	return (1);
}
