/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 12:39:13 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/01 17:06:59 by mskerba          ###   ########.fr       */
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
		if (!var[i + 1] && var[i] == '+' && val)
			break ;
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
	}
	return (0);
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
		if (cmd->args[i][0] == '=')
		{
			cmd->error = 1;
			put_error_two("export", cmd->args[i], "not a valid identifier");
		}
		else if (check_var(var, val))
		{
			cmd->error = 1;
			put_error_two("export", cmd->args[i], "not a valid identifier");
		}
		else if (var[ft_strlen(var) - 1] == '+')
		{
			var[ft_strlen(var) - 1] = 0;
			val = join_val(val, ft_strdup(var));
			if (ft_getenv(var))
				we_unset(var);
			printf("%s\n",var);
			g_global.env = ft_realloc(g_global.env, ft_strdup(val));
		}
		else if (!val && is_duplicated(get_var(cmd->args[i])))
		{
			free(var);
			free(val);
			continue ;
		}
		else if (var && !is_duplicated(get_var(cmd->args[i])))
			g_global.env = ft_realloc(g_global.env, ft_strdup(cmd->args[i]));
		else
		{
			we_unset(var);
			g_global.env = ft_realloc(g_global.env, ft_strdup(cmd->args[i]));
		}
		free(var);
		free(val);
	}
	return (1);
}
