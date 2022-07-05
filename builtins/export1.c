/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:39:13 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/05 16:09:26 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_val(char *val, char *var)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	str = ft_getenv(var);
	free(var);
	if (str)
	{
		var = ft_strjoin(tmp, str);
		free(str);
		str = ft_strjoin(var, val);
		free(var);
	}
	else
		str = ft_strjoin(tmp, val);
	free(tmp);
	free(val);
	return (str);
}

int	check_var(char *var, char *val)
{
	int	i;

	i = -1;
	if (ft_isdigit(var[0]))
		return (1);
	while (var[++i])
	{
		if (!var[i + 1] && var[i] == '+' && val && i)
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
	}
	return (0);
}

int	change_val(char *var, char *val, int i, t_cmd *cmd)
{
	if (!val && is_duplicated(get_var(cmd->args[i])))
	{
		free(var);
		free(val);
		return (1);
	}
	else if (var && !is_duplicated(get_var(cmd->args[i])))
		g_global.env = ft_realloc(g_global.env, ft_strdup(cmd->args[i]));
	else
	{
		we_unset(var);
		g_global.env = ft_realloc(g_global.env, ft_strdup(cmd->args[i]));
	}
	return (0);
}

int	add_val(char *var, char *val, int i, t_cmd *cmd)
{
	char	*env;

	if (check_var(var, val))
	{
		cmd->error = 1;
		put_error_two("export", cmd->args[i], "not a valid identifier");
	}
	else if (var[ft_strlen(var) - 1] == '+')
	{
		var[ft_strlen(var) - 1] = 0;
		val = join_val(val, ft_strdup(var));
		env = ft_getenv(var);
		if (env)
		{
			we_unset(var);
			free(env);
		}
		g_global.env = ft_realloc(g_global.env, ft_strdup(val));
	}
	else if (change_val(var, val, i, cmd))
		return (1);
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	char	*val;
	char	*var;
	int		i;

	i = 0;
	if (!cmd->args[1])
		print_export(cmd);
	while (cmd->args[++i])
	{
		var = get_var(cmd->args[i]);
		val = get_val(cmd->args[i]);
		if (cmd->args[i][0] == '=')
		{
			cmd->error = 1;
			put_error_two("export", cmd->args[i], "not a valid identifier");
		}
		else if (add_val(var, val, i, cmd))
			continue ;
		free(var);
		free(val);
	}
	return (1);
}
