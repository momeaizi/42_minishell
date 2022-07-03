/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:03:52 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/03 01:34:17 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	dollar_counter(char *str, t_expand_var *exp_var)
{
	int		i;

	i = -1;
	exp_var->count = 0;
	exp_var->double_qoute = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
			exp_var->double_qoute = !exp_var->double_qoute;
		i += ignore_quotes(str + i, exp_var);
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) \
		|| str[i + 1] == '_' || str[i + 1] == '?'))
			exp_var->count++;
		else if (str[i] == '$' && str[i] == str[i + 1])
			i++;
	}
}

void	get_variable(t_env_var	*env_var, char expand_all)
{
	char	*var;

	env_var->end = 1;
	if (!env_var->var_len)
		env_var->var_len = 1;
	var = env_var->var;
	env_var->var = (char *)malloc((env_var->var_len + 1) * sizeof(char));
	if (!env_var->var)
		return ;
	ft_strlcpy(env_var->var, var, env_var->var_len + 1);
	if (!ft_strcmp("?", env_var->var))
		env_var->val = ft_itoa(g_global.error);
	else
		env_var->val = ft_getenv(env_var->var);
	if (!env_var->val)
		env_var->val = ft_strdup("");
	env_var->val_len = ft_strlen(env_var->val);
	if (!expand_all)
		replace(replace(env_var->val, '\'', -4), '\"', -5);
}

void	replace_var_by_val(char *str, t_expand_var *exp_var)
{
	int		i;
	int		j;
	int		index;

	set_len(exp_var, &index, &i, &j);
	if (!i)
		return ;
	while (str[++i])
	{
		is_quote(str[i], exp_var);
		if (exp_var->expnd && str[i] == '$' && \
		(ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			ft_strlcpy(exp_var->new_str + j, exp_var->env_var[index].val, \
			exp_var->env_var[index].val_len + 1);
			i += exp_var->env_var[index].var_len;
			j += exp_var->env_var[index].val_len ;
			index++;
		}
		else
			exp_var->new_str[j++] = exp_var->str[i];
	}
	exp_var->new_str[j] = 0;
}

void	expander(char *str, t_expand_var *exp_var, char expand_all)
{
	int	i;
	int	index;

	i = -1;
	index = 0;
	while (++i < exp_var->str_len)
	{
		if (str[i] == '\"')
			exp_var->double_qoute = !exp_var->double_qoute;
		i += ignore_quotes(str + i, exp_var);
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) \
		|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			exp_var->env_var[index].var_len = 0;
			exp_var->env_var[index].var = &str[i] + 1;
			while (ft_isalpha(str[++i]) || str[i] == '_')
				exp_var->env_var[index].var_len++;
			i--;
			get_variable(&exp_var->env_var[index], expand_all);
			index++;
		}
		else if (str[i] == '$' && str[i] == str[i + 1])
			i++;
	}
	exp_var->env_var[index].end = 0;
}

char	*expand_var(char *str, char expand_all)
{
	t_expand_var	*exp_var;
	char			*new_str;

	exp_var = NULL;
	exp_var = init(exp_var, str, expand_all);
	if (!exp_var || !exp_var->count)
	{
		if (exp_var)
			free(exp_var);
		return (str);
	}
	expander(str, exp_var, expand_all);
	replace_var_by_val(str, exp_var);
	new_str = exp_var->new_str;
	if (!expand_all)
		new_str = is_empty(exp_var->new_str);
	clear_env(exp_var->env_var);
	free(str);
	free(exp_var);
	return (new_str);
}
