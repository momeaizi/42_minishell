/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:07:05 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/29 10:57:12 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_path(char *path, char **paths)
{
	char	*cmd_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], path);
		if (!access(cmd_path, X_OK))
		{
			clear(paths, size_double(paths));
			free(path);
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = NULL;
	}
	clear(paths, size_double(paths));
	free(path);
	return (NULL);
}

char	*get_cmd_path(char *cmd_name)
{
	char	*path;
	char	**paths;
	int		i;

	if (!access(cmd_name, X_OK))
		return (ft_strdup(cmd_name));
	else if (!ft_strlen(cmd_name))
		return (NULL);
	i = -1;
	path = ft_getenv("PATH");
	if (!path)
		return (NULL);
	split(&paths, path, ':');
	free(path);
	path = ft_strjoin("/", cmd_name);
	return (search_in_path(path, paths));
}

