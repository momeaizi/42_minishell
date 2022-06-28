/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:03 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/27 11:42:01 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*tokens_length(char *str, char c)
{
	int	i;
	int	j;
	int	*size;
	int	count;

	count = count_tokens(str, c) - 1;
	i = 0;
	j = -1;
	size = (int *)malloc(count * sizeof(int));
	if (!size)
		return (NULL);
	while (++j < count)
		size[j] = 1;
	j = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] != c)
			size[j]++;
		else if (str[i] == c && str[i + 1] != c)
			j++;
		i++;
	}
	return (size);
}
