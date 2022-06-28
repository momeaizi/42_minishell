/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:35:55 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/27 11:41:10 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokens(char *str, char c)
{
	int	i;
	int	count;

	replace_inside_quotes(str, -1, c);
	i = -1;
	count = 1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (i == 0 && str[i] != c)
			count++;
		else if (str[i] != c && str[i - 1] == c)
			count++;
	}
	return (count);
}
