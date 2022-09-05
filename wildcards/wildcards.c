/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:42:39 by mskerba           #+#    #+#             */
/*   Updated: 2022/09/04 15:35:50 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wildcards(char *arg, char *dir_content)
{
	if (is_all_asterisk(arg))
	{
		if (dir_content[0] != '.')
			return (1);
		return (0);
	}
	else if (!strcmp(dir_content, "..") || !strcmp(dir_content, "."))
		return (0);
	else if (!first_char(arg, dir_content) || !last_char(arg, dir_content))
		return (0);
	else if (filter(arg, dir_content))
		return (1);
	return (0);
}

char	**asterisk(char *arg)
{
	struct dirent	*dir_content;
	DIR				*current_dir;
	char			**new_arg;
	char			*path;

	path = getcwd((void *)0, 0);
	new_arg = ft_calloc(1, sizeof(char *));
	if (!path)
	{
		new_arg = ft_realloc(new_arg, arg);
		return (new_arg);
	}
	current_dir = opendir(path);
	while (1)
	{
		dir_content = readdir(current_dir);
		if (!dir_content)
			break ;
		if (wildcards(arg, dir_content->d_name))
		{
			new_arg = ft_realloc(new_arg, ft_strdup(dir_content->d_name));
		}
	}
	closedir(current_dir);
	return (new_arg);
}
