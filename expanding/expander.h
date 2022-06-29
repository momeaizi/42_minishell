/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:58:51 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/23 00:45:40 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"

typedef struct s_env_var
{
	char	*var;
	char	*val;
	int		var_len;
	int		val_len;
	char	end;
}	t_env_var;

typedef struct s_expand_var
{
	char		double_qoute;
	char		expnd;
	char		expand_all;
	char		*str;
	char		*new_str;
	int			str_len;
	int			new_str_len;
	int			count;
	t_env_var	*env_var;
}	t_expand_var;

t_expand_var	*init(t_expand_var *exp_var, char *str, char expand_all);
int				ignore_quotes(char *str, t_expand_var *exp_var);
void			dollar_counter(char *str, t_expand_var *exp_var);
void			clear_env(t_env_var *env_var);
void			get_variable(t_env_var	*env_var, char expand_all);
char			*is_empty(char *str);
void			set_len(t_expand_var *exp_var, int *index, int *i, int *j);
void			is_quote(char c, t_expand_var *exp_var);
#endif