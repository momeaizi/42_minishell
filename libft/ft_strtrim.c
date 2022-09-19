/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:20:08 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/19 19:37:58 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	size_t	i;
	size_t	end;
	size_t	start;

	if (!s1 || !ft_strlen(s1))
		return (ft_calloc(1, sizeof(char)));
	str = NULL;
	i = 0;
	end = ft_strlen(s1) - 1;
	start = 0;
	while (is_set(s1[start], set))
		start++;
	while (end > start && is_set(s1[end], set))
		end--;
	str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
