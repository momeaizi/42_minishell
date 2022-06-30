/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:15:08 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 12:55:59 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	write(cmd->out, path, ft_strlen(path));
	write(cmd->out, "\n", 1);
	return (1);
}
