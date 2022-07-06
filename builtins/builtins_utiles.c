/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:51:14 by mskerba           #+#    #+#             */
/*   Updated: 2022/07/06 12:12:19 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *args)
{
	char	*var;
	char	c;
	int		i;

	i = -1;
	while (args[++i] != '=' && args[i])
		;
	c = args[i];
	args[i] = 0;
	var = ft_strdup(args);
	if (c)
		args[i] = '=';
	return (var);
}

char	*get_val(char *args)
{
	int	i;

	i = -1;
	while (args[++i] != '=' && args[i])
		;
	if (args[i])
		return (ft_strdup(args + i + 1));
	return (NULL);
}

void	print_export(t_cmd *cmd)
{
	char	*vars[2];
	int		i;

	i = -1;
	while (g_global.env[++i])
	{
		vars[0] = get_var(g_global.env[i]);
		vars[1] = get_val(g_global.env[i]);
		write(cmd->out, "declare -x ", 11);
		write(cmd->out, vars[0], ft_strlen(vars[0]));
		if (vars[1])
		{
			write(cmd->out, "=\"", 2);
			write(cmd->out, vars[1], ft_strlen(vars[1]));
			write(cmd->out, "\"", 1);
		}
		write(cmd->out, "\n", 1);
		free(vars[0]);
		if (vars[1])
			free(vars[1]);
	}
}

int	is_duplicated(char *var)
{
	char	*val;
	int		i;

	i = -1;
	if (var[ft_strlen(var) - 1] == '+')
		var[ft_strlen(var) - 1] = 0;
	while (g_global.env[++i])
	{
		val = get_var(g_global.env[i]);
		if (!ft_strcmp(var, val))
		{
			free(val);
			free(var);
			return (1);
		}
		free(val);
	}
	free(var);
	return (0);
}

void	we_unset(char *var_to_unset)
{
	char	**new_env;
	char	*var;
	int		i;
	int		j;

	j = 0;
	i = -1;
	new_env = ft_calloc(size_double(g_global.env), sizeof(char *));
	while (g_global.env[++i])
	{
		var = get_var(g_global.env[i]);
		if (ft_strcmp(var_to_unset, var))
			new_env[j++] = g_global.env[i];
		else
			free(g_global.env[i]);
		free(var);
	}
	free(g_global.env);
	g_global.env = new_env;
}
