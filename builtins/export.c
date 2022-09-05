/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 23:58:06 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/04 18:34:10 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_env(char *var)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	while (g_global.env[++i])
		if ((!ft_strncmp(g_global.env[i], var, len) \
		&& g_global.env[i][len] == '=') || !ft_strcmp(g_global.env[i], var))
			return (1);
	return (0);
}

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

void	export_part(t_cmd *cmd, char *var, char *val, int i)
{
	if (var[ft_strlen(var) - 1] == '+')
	{
		var[ft_strlen(var) - 1] = 0;
		val = join_val(val, ft_strdup(var));
		if (is_in_env(var))
			we_unset(var);
		g_global.env = ft_realloc(g_global.env, ft_strdup(val));
		free(var);
		free(val);
	}
	else if (!val && is_duplicated(get_var(cmd->args[i])))
		free(var);
	else if (var && !is_duplicated(get_var(cmd->args[i])))
	{
		g_global.env = ft_realloc(g_global.env, ft_strdup(cmd->args[i]));
		free(var);
		free(val);
	}
	else
	{
		we_unset(var);
		g_global.env = ft_realloc(g_global.env, ft_strdup(cmd->args[i]));
		free(var);
		free(val);
	}
}

void	ft_export(t_cmd *cmd)
{
	char	*var;
	char	*val;
	int		i;

	i = 0;
	if (!cmd->args[1])
		print_export(cmd);
	while (cmd->args[++i])
	{
		var = get_var(cmd->args[i]);
		val = get_val(cmd->args[i]);
		if (cmd->args[i][0] == '=' || check_var(var, val))
		{
			cmd->error = 2;
			put_error_two("export", cmd->args[i], "not a valid identifier");
			free(var);
			free(val);
		}
		else
			export_part(cmd, var, val, i);
	}
}
