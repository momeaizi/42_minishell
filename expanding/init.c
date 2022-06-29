/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:54:46 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/29 11:48:03 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expand_var	*init(t_expand_var *exp_var, char *str, char expand_all)
{
	exp_var = (t_expand_var *)malloc(sizeof(t_expand_var));
	if (!exp_var)
		return (NULL);
	exp_var->double_qoute = 0;
	exp_var->expnd = 1;
	exp_var->expand_all = expand_all;
	exp_var->str = str;
	exp_var->new_str = NULL;
	exp_var->str_len = ft_strlen(str);
	exp_var->new_str_len = ft_strlen(str) + 1;
	dollar_counter(str, exp_var);
	if (exp_var->count)
		exp_var->env_var = (t_env_var *)malloc((exp_var->count + 1) \
		* sizeof(t_env_var));
	return (exp_var);
}
