/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:14:09 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/02 17:27:25 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	new_pwd(char *old_pwd, char *pwd)
{
	int	i;
	int	flag;

	flag = 1;
	i = -1;
	while (g_global.env[++i])
	{
		if (!ft_strncmp(g_global.env[i], "PWD", 3) && g_global.env[i][3] == '=')
		{
			free(g_global.env[i]);
			g_global.env[i] = pwd;
		}
		else if (!ft_strncmp(g_global.env[i], "OLDPWD", 6)
			&& g_global.env[i][6] == '=')
		{
			free(g_global.env[i]);
			g_global.env[i] = old_pwd;
			flag = 0;
		}
	}
	if (flag)
		g_global.env = ft_realloc(g_global.env, old_pwd);
}

void	change_pwd(void)
{
	char	*val;
	char	*old_pwd;
	char	*pwd;

	pwd = NULL;
	val = expand_var(ft_strdup("$PWD"), 0);
	old_pwd = ft_strjoin("OLDPWD=", val);
	free(val);
	val = getcwd(NULL, 0);
	if (val)
	{
		pwd = ft_strjoin("PWD=", val);
		free(val);
	}
	new_pwd(old_pwd, pwd);
}

int	ft_cd(t_cmd *cmd)
{
	char	*path;
	int		ret;

	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
	{
		path = expand_var(ft_strdup("$HOME"), 0);
		ret = chdir(path);
		free(path);
	}
	else
		ret = chdir(cmd->args[1]);
	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "cd: error retrieving current directory: getcwd: cannot",54);
		write(2, "access parent directories: No such file or directory\n", 53);
	}
	else if (ret < 0)
	{
		put_error_two("cd", cmd->args[1], strerror(errno));
		cmd->error = 1;
	}
	if (path)
		free(path);
	change_pwd();
	return (1);
}
