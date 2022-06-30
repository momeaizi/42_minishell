/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:39:13 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 12:58:24 by momeaizi         ###   ########.fr       */
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

int	ft_export(t_cmd *cmd)
{
	char	*val;
	char	*var;
	int		i;
	int		j;

	i = 0;
	if (!cmd->args[1])
		print_export(cmd);
	while (cmd->args[++i])
	{
		var = get_var(cmd->args[i]);
		val = get_val(cmd->args[i]);
		j = 0;
		if (var)
			g_global.env = ft_realloc(g_global.env, ft_strdup(cmd->args[i]));
		free(var);
		free(val);
	}
	return (1);
}
