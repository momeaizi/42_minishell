/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:32:50 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 16:13:47 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	c = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != c && str[i])
		i++;
	if (str[i] == c)
		return (str + i);
	return (0);
}
/*#include<stdio.h>
int	main()
{
	printf("%s\n", ft_strchr("tripouille", 't' + 256));
}*/
