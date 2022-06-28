/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_car.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 10:25:14 by mskerba           #+#    #+#             */
/*   Updated: 2022/06/27 08:00:20 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_space(char *line, int i)
{
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
