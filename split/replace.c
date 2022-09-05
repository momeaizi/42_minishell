/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 11:46:38 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/04 15:36:24 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_all_strings(char *str, char **strs, char new, char old)
{
	int	i;

	i = -1;
	while (strs[++i])
		replace_inside_quotes(strs[i], new, old);
	replace_inside_quotes(str, new, old);
}

void	replace_inside_quotes(char *str, char new, char old)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			j = i;
			i++;
			while (str[i] && str[i] != str[j])
			{
				if (str[i] == old)
					str[i] = new;
				i++;
			}
		}
	}
}

char	*replace(char *str, char old, char new)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == old)
			str[i] = new;
	return (str);
}

void	remove_tab(char *str)
{
	if (!str)
		return ;
	replace_inside_quotes(str, -1, '\t');
	replace(str, '\t', ' ');
	replace_inside_quotes(str, '\t', -1);
}
