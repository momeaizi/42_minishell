/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:14:09 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 06:48:08 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		ret;

	path = NULL;
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
	{
		path = expand_var(ft_strdup("$HOME"), 0);
		ret = chdir(path);
		free(path);
	}
	else
		ret = chdir(cmd->args[1]);
	path = getcwd(path, sizeof(path));
	if (!path)
		write(2, "cd: error retrieving current directory: getcwd: cannot \
		access parent directories: No such file or directory\n",
			108);
	else if (ret < 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	return (1);
}
