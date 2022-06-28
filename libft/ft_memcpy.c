/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:09:31 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 15:58:45 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cdest;
	unsigned char	*csrc;

	cdest = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dst);
}

/*#include <stdio.h>
#include <string.h>
int main()
{
   char	csrc[4] = "hel";
   char	dest[4];
   char	*p = ft_memcpy(0, 0, 4 * sizeof(char));
   //for(int i  = 0; i< 4;i++)
   //{
   	printf("%p\n", p);
   //}
   return 0;
}*/
