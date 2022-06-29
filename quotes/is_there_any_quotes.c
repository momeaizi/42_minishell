/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_any_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:22:41 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/22 10:39:00 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_any_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	return (0);
}
