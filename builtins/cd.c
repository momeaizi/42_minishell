/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:14:09 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 15:11:58 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(void)
{
	char	*val;
	char	*old_pwd;
	char	*pwd;
	int		i;

	val = expand_var(ft_strdup("$PWD"), 0);
	old_pwd = ft_strjoin("OLDPWD=", val);
	free(val);
	val = getcwd(NULL, 0);
	if (val)
	{
		pwd = ft_strjoin("PWD=", val);
		free(val);
	}
	i = -1;
	while (g_global.env[++i])
	{
		if (!ft_strncmp(g_global.env[i], "PWD", 3) && g_global.env[i][3] == '=')
		{
			free(g_global.env[i]);
			g_global.env[i] = pwd;
		}
		else if (!ft_strncmp(g_global.env[i], "OLDPWD", 6) \
			&& g_global.env[i][6] == '=')
		{
			free(g_global.env[i]);
			g_global.env[i] = old_pwd;
		}
	}
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
	if (path)
		free(path);
	change_pwd();
	return (1);
}
