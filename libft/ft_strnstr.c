/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:12:16 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 16:37:44 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char	*str;

	str = (char *)haystack;
	length = ft_strlen(needle);
	if (!length)
		return (str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		if (str[i] == needle[j])
		{
			while ((str[i + j] == needle[j]) && str[i + j] && (i + j) < len)
				j++;
			if (j == length)
				return (str + i);
		}
		i++;
	}
	return (NULL);
}

/*#include<string.h>
#include<stdio.h>

int	main()
{

	printf("%s\n", ft_strnstr("aaabcabcd", "aabc", -1));
}*/
