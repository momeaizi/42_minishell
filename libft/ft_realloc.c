/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:20:46 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 18:44:57 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc(char **strs, char *str)
{
	char	**new_strs;
	int		i;

	i = -1;
	new_strs = (char **)ft_calloc(size_double(strs) + 2, sizeof(char *));
	if (!new_strs)
		return (strs);
	while (strs[++i])
		new_strs[i] = strs[i];
	new_strs[i] = str;
	free(strs);
	return (new_strs);
}
