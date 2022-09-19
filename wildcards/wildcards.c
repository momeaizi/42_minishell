/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:42:39 by mskerba           #+#    #+#             */
/*   Updated: 2022/09/18 20:15:25 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wildcards(char *arg, char *dir_content)
{
	if (!ft_strlen(arg))
		return (0);
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

char	**asterisk(char *arg, char **args, int size)
{
	struct dirent	*dir_content;
	DIR				*dir;
	char			*path;

	replace_inside_quotes(arg, -7, '*');
	arg = remove_quotes(arg);
	path = getcwd((void *)0, 0);
	if (!path)
		return (ft_realloc(args, arg));
	dir = opendir(path);
	free(path);
	if (dir < 0)
		return (ft_realloc(args, arg));
	while (1)
	{
		dir_content = readdir(dir);
		if (!dir_content)
			break ;
		if (wildcards(arg, dir_content->d_name))
			args = ft_realloc(args, ft_strdup(dir_content->d_name));
	}
	closedir(dir);
	replace(arg, -7, '*');
	if (size == size_double(args))
		return (ft_realloc(args, arg));
	free(arg);
	return (args);
}
