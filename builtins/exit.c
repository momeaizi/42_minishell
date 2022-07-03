/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:16:43 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/03 03:48:29 by momeaizi         ###   ########.fr       */
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
	if(cmd->args[1] && cmd->args[2])
	{
		if(!check_args_exit(cmd->args[1]))
		{
			cmd->error = 255;
			put_error_two("exit", cmd->args[1], "numeric argument required");
		}
		else
		{
			cmd->error = 1;
			put_error_two("exit", cmd->args[1], "too many arguments");
		}
			
	}
	else if (!cmd->args[1])
		exit(g_global.error);
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
