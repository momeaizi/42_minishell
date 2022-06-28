/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 20:19:45 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 15:53:10 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	c = (unsigned char)c;
	s1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s1[i] == c)
			return (((void *)s1 + i));
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
#include<string.h>
int	main()
{
	char	arr[] = "hello";
	char	*arr1 = (char *)memchr(arr, 'm', 5 * sizeof(char));
	printf("%p\n", arr1);
	printf("%c\n", arr1[1]);
	printf("%c\n", arr1[2]);
	printf("%c\n", arr1[3]);
}*/
