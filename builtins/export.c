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