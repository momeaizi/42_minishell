/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:42:39 by mskerba           #+#    #+#             */
/*   Updated: 2022/08/30 15:19:55 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_content(char *arg, char *dir_content)
{
	if (check_char(arg))
	{
		if (dir_content[0] != '.')
			return (1);
		return (0);
	}
	else if (!strcmp(dir_content,"..") || !strcmp(dir_content,"."))
		return (0);
	else if (!check_start(arg,dir_content) || !check_end(arg,dir_content))
		return (0);
	else if (check_all(arg,dir_content))
		return (1);
	return (0);	
}

char **wildcards(char *arg, char **new_arg)
{
	struct	dirent *dir_content;
	DIR		*current_dir;
	char	*path;

	path = getcwd(NULL,0);
	// new_arg = ft_calloc(1,sizeof(char *));
	if (!path)
		return(ft_realloc(new_arg,ft_strdup(arg)));
	current_dir = opendir(path);
	if (!current_dir)
		return(ft_realloc(new_arg,ft_strdup(arg)));
	while (1)
	{
		dir_content = readdir(current_dir);
		if (!dir_content)
			break;
		if (check_content(arg, dir_content->d_name))
			new_arg = ft_realloc(new_arg,ft_strdup(dir_content->d_name));
	}
	closedir(current_dir);
	return (new_arg);
}
