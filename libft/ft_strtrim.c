/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:20:08 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 16:52:08 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
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

/*int main(void)
{
    char    arr[] = "";
    char    p = NULL;
    printf("%s\n",ft_strtrim("acbaXXXb", "acb"));
    printf("%p\n", p);
}*/
