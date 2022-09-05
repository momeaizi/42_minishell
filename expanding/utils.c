/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:49:34 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/04 15:40:37 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	ignore_quotes(char *str, t_expand_var *exp_var)
{
	int	i;

	i = 0;
	if (exp_var->expand_all)
		return (0);
	if (str[i] == '\'' && !exp_var->double_qoute)
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			return (i);
		return (1);
	}
	return (0);
}

int	get_var_len(char *str)
{
	int	i;

	i = -1;
	if (ft_isdigit(str[0]))
		return (1);
	while (ft_isalnum(str[++i]) || str[i] == '_')
		;
	return (i);
}

char	*is_empty(char *str)
{
	char	*new_str;

	if (!ft_strcmp("\"\"", str))
	{
		new_str = ft_strdup(" ");
		free(str);
		return (new_str);
	}
	return (str);
}

void	set_len(t_expand_var *exp_var, int *index, int *i, int *j)
{
	*i = -1;
	while (exp_var->env_var[++*i].end)
		exp_var->new_str_len += (exp_var->env_var[*i].val_len
				- exp_var->env_var[*i].var_len);
	exp_var->new_str = (char *)malloc(exp_var->new_str_len * sizeof(char));
	*i = -1;
	*j = 0;
	*index = 0;
	if (!exp_var->new_str)
		i = 0;
}

void	is_quote(char c, t_expand_var *exp_var)
{
	if (c == '\"')
		exp_var->double_qoute = !exp_var->double_qoute;
	else if (c == '\'' && !exp_var->expnd)
		exp_var->expnd = 1;
	else if (c == '\'' && !exp_var->double_qoute && !exp_var->expand_all)
		exp_var->expnd = 0;
}
