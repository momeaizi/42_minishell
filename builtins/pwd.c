/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:15:08 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 06:48:33 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	*path;

	path = NULL;
	path = getcwd(path, sizeof(path));
	if (!path)
		return (1);
	write(cmd->out, path, ft_strlen(path));
	write(cmd->out, "\n", 1);
	return (1);
}
