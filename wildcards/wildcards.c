/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:42:39 by mskerba           #+#    #+#             */
/*   Updated: 2022/08/30 11:44:46 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char	*ft_strcpy(char	*dest, const char	*src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	len = i + ft_strlen(s2) + 1;
	res = (char *)malloc(len * sizeof(char));
	if (!res)
		return (0);
	ft_strcpy(res, (char *)s1);
	ft_strcpy(res + i, (char *)s2);
	return (res);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	i;

	i = ft_strlen(s1);
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	return (ft_strcpy(dest, s1));
}


int check_char(char *arg)
{
    int i;

    i = -1;
    while (arg[++i])
        if(arg[i] != '*')
            return (0);
    return (1);
}

int check_end(char *arg, char *dir_content)
{
    if (arg[ft_strlen(arg) - 1] != dir_content[ft_strlen(dir_content) - 1] && arg[ft_strlen(arg) - 1] != '*')
        return (0);

    return (1);
}

int check_start(char *arg, char *dir_content)
{
    if (arg[0] != dir_content[0] && arg[0] != '*')
        return (0);
    return (1);
}

int check_all(char *arg, char *dir_content)
{
    int i;
    int j;


    i = -1;
    j = -1;
    while (arg[++i])
    {
        if (arg[i] != '*')
        {
            while(1)
            {
                if (!dir_content[j])
                    return (0);
                else if (dir_content[++j] == arg[i])
                    break;
            }
        }
    }
    return (1);
}

//delete!|^

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

char *wildcards(char *arg, char *path) //path is the $PWD
{
	struct	dirent *dir_content;
	DIR		*current_dir;
	char	*new_arg;
	// char	*path;

	// path = ft_getenv("PWD");
	//protect null path
	current_dir = opendir(path);
	//permition denied
	new_arg = ft_strdup("");
	while (1)
	{
		dir_content = readdir(current_dir);
		if (!dir_content)
			break;
		if (check_content(arg, dir_content->d_name))
		{
			if(new_arg[0])
				new_arg = ft_strjoin(new_arg, " ");
			new_arg = ft_strjoin(new_arg,dir_content->d_name);
		}
	}
	closedir(current_dir);
	return (new_arg);
}

int main(int c, char **v)
{
	(void)c;

	printf("%s\n", wildcards(v[1], "/home/mskerba/Desktop/42_minishell"));
}