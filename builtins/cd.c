/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:14:09 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/06 00:27:03 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_var(char *var, char *val)
{
	char	*tmp;

	tmp = ft_getenv(var);
	if (tmp)
	{
		we_unset(var);
		free(tmp);
	}
	tmp = ft_strjoin(var, "=");
	if (!val)
		val = ft_strdup("");
	var = ft_strjoin(tmp, val);
	free(val);
	free(tmp);
	g_global.env = ft_realloc(g_global.env, var);
}

void	print_error_cd(void)
{
	write(2, "cd: error retrieving current directory: ", 40);
	write(2, "getcwd: cannot access parent directories: ", 43);
	write(2, "No such file or directory\n", 27);
}

void	check_error_cd( t_cmd *cmd, char *path, int ret)
{	
	if (!path)
		print_error_cd();
	else if (ret < 0)
	{
		cmd->error = 1;
		put_error_two("cd", cmd->args[1], strerror(errno));
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		ret;

	if (!cmd->args[1])
	{
		path = ft_getenv("HOME");
		if (!path)
		{
			put_error("cd", "HOME not set");
			return ;
		}
		ret = chdir(path);
		free(path);
	}
	else
		ret = chdir(cmd->args[1]);
	path = getcwd(NULL, 0);
	check_error_cd(cmd, path, ret);
	if (path)
		free(path);
}
