/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:39:13 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/29 21:13:25 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = -1;
		if (args[i][0] == '-')
			j++;
		while (args[i][++j])
			if (args[i][j] != 'n')
				return (i);
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	j;

	j = check_n(cmd->args);
	i = j - 1;
	while (cmd->args[++i])
	{
		if (i != j)
			write(cmd->out, " ", 1);
		write(cmd->out, cmd->args[i], strlen(cmd->args[i]));
	}
	if (j == 1)
		write(cmd->out, "\n", 1);
	return (1);
}

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

int	ft_pwd(t_cmd *cmd)
{
	char	*path;

	path = NULL;
	path = getcwd(path, sizeof(path));
	if (!path)
		return (1);
	write(cmd->out, path, ft_strlen(path));
	write(cmd->out, "\n", 1);
	return (1);
}

int	ft_export(t_cmd *cmd)
{
	(void)cmd;
	return (1);
}

int	check_env_var(t_cmd *cmd, char *env)
{
	int	len;
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		len = ft_strlen(cmd->args[i]);
		if (ft_strncmp(env, cmd->args[i], len) || env[len] != '=')
			return (0);
	}
	return (1);
}

int	ft_unset(t_cmd *cmd)
{
	char	*var;
	char	**new_env;
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	j = 0;
	while (cmd->args[++i])
	{
		var = ft_getenv(cmd->args[i]);
		if (var)
		{
			free(var);
			count++;
		}
	}
	new_env = ft_calloc(size_double(g_global.env) - count + 1, sizeof(char *));
	i = -1;
	while (g_global.env[++i])
	{
		if (!check_env_var(cmd, g_global.env[i]))
		{
			new_env[j] = ft_strdup(g_global.env[i]);
			free(g_global.env[i]);
			j++;
		}
	}
	free(g_global.env);
	g_global.env = new_env;
	return (1);
}

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->args[1])
		return (1);
	while (g_global.env[++i])
	{
		write(cmd->out, g_global.env[i], ft_strlen(g_global.env[i]));
		write(cmd->out, "\n", 1);
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	if (!cmd->args[2])
	{
		write(2, "exit\nbash: exit: ", 17);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	else if (ft_atoi(cmd->args[1]) >= INT_MAX
			|| ft_atoi(cmd->args[1]) <= INT_MIN)
	{
		write(2, "exit\nbash: exit: ", 17);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(ft_atoi(cmd->args[1]));
	}
	else
		exit(ft_atoi(cmd->args[1]));
	return (1);
}
