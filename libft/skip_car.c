/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_car.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 10:25:14 by mskerba           #+#    #+#             */
/*   Updated: 2022/09/20 15:55:16 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_space(char *line, int i)
{
	while (line[++i] && line[i] == ' ')
		;
	return (i);
}

int	skip_space2(char *line, int i)
{
	if (line[i] == ' ')
		while (line[++i] && line[i] == ' ')
			;
	return (i);
}

int	skip_quotes(char *line, int i, char quote)
{
	if (line[i] != '\'' && line[i] != '\"')
		;
	else
		while (line[++i] && line[i] != quote)
			;
	return (i);
}

int	skip_brackets(char *line, int i)
{
	int	j;

	j = 1;
	if (line[i] == '(')
	{
		while (line[++i] && j)
		{
			if (line[i] == '(')
				j++;
			if (line[i] == ')')
				j--;
		}
	}
	return (i);
}
// (ls && ps) || df && (uname -a | grep 1337 || ls)