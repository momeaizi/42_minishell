/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 06:15:42 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 14:25:16 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static int	is_valid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

void	check_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (!is_valid(cmd->args[i]))
		{
			put_error_two("unset", cmd->args[i], "not a valid identifier");
			cmd->error = 1;
		}
	}
}

int	size_env(t_cmd *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (g_global.env[++i])
	{
		if (!check_env_var(cmd, g_global.env[i]))
			continue ;
		count++;
	}
	return (count);
}

int	ft_unset(t_cmd *cmd)
{
	char	**new_env;
	int		i;
	int		j;
	int		count;

	count = size_env(cmd);
	check_args(cmd);
	if (!count)
		return (1);
	j = 0;
	new_env = ft_calloc(size_double(g_global.env) - count + 1, sizeof(char *));
	i = -1;
	while (g_global.env[++i])
	{
		if (!check_env_var(cmd, g_global.env[i]))
			new_env[j++] = ft_strdup(g_global.env[i]);
		free(g_global.env[i]);
	}
	free(g_global.env);
	g_global.env = new_env;
	return (1);
}
