/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:32:50 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/18 20:10:03 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	c = (char)c;
	str = (char *)s;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (str + i);
	return (0);
}
