/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:07:05 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/06 14:49:15 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_cmd_path(t_cmd *cmd, char *cmd_name)
{
	char	*path;
	char	**paths;
	int		i;

	if (!ft_strlen(cmd_name))
		return (NULL);
	else if (!access(cmd_name, X_OK))
		return (ft_strdup(cmd_name));
	i = -1;
	path = ft_getenv("PATH");
	if (!path)
	{
		cmd->error = 127;
		put_error(cmd_name, "No such file or directory");
		return (NULL);
	}
	split(&paths, path, ':');
	free(path);
	path = ft_strjoin("/", cmd_name);
	return (search_in_path(path, paths));
	return (path);
}

char	*get_path(t_cmd *cmd, char *cmd_name)
{
	char	*path;
	DIR		*pdir;

	path = get_cmd_path(cmd, cmd_name);
	if (!path && !cmd->error)
	{
		cmd->error = 127;
		if (ft_strchr(cmd_name, '/'))
			put_error(cmd_name, "No such file or directory");
		else
			put_error(cmd_name, "command not found");
	}
	else if (ft_strchr(cmd_name, '/'))
	{
		pdir = opendir(path);
		if (!pdir)
			return (path);
		cmd->error = 126;
		closedir(pdir);
		put_error(cmd_name, "is a directory");
	}
	return (path);
}
