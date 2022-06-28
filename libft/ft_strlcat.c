/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 10:50:10 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 16:24:52 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (!dstsize)
		return (ft_strlen(src));
	i = 0;
	j = ft_strlen(dst);
	while (src[i] && j < (dstsize - i - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j >= dstsize)
		return (dstsize + ft_strlen(src));
	dst[j + i] = 0;
	return (ft_strlen(src) + j);
}

/*#include <stdio.h>
# include <string.h>

int	main()
{
	char	dest[15];
	memset(dest, 'r', 15);
	printf("%lu\n", ft_strlcat(dest, "lorem ipssum dolor sit amet", 15));
	printf("%s\n",dest);
}*/
