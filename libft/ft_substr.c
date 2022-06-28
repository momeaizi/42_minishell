/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:44:20 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 16:45:45 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= len)
		len = s_len - start;
	if (start > s_len || !len)
		return (ft_calloc(1, sizeof(char)));
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}

/*#include <stdio.h>

int	main()
{
	printf("%s\n", ft_substr("42", 0, 0));
}*/
