/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:13:22 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 06:14:02 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = -1;
		if (args[i][0] == '-')
			j++;
		while (args[i][++j])
			if (args[i][j] != 'n')
				return (i);
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	j = check_n(cmd->args);
	i = j - 1;
	while (cmd->args[++i])
	{
		if (i != j)
			write(cmd->out, " ", 1);
		write(cmd->out, cmd->args[i], strlen(cmd->args[i]));
	}
	if (j == 1)
		write(cmd->out, "\n", 1);
	return (1);
}
