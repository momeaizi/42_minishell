/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:35:42 by momeaizi          #+#    #+#             */
/*   Updated: 2021/11/20 14:15:08 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	ft_check(long nb, int signe)
{
	if (nb < 0)
	{
		if (signe == 1)
			return (-1);
		else if (signe == -1)
			return (0);
	}
	return (signe * nb);
}

int	ft_atoi(const char *str)
{
	long	nb;
	int		i;
	int		signe;

	nb = 0;
	i = 0;
	signe = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		signe = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	return (ft_check(nb, signe));
}
/*#include <stdio.h>
#include <stdlib.h>
int	main(int	ac, char	**av)
{
	printf("%d\n", atoi(av[1]));
	printf("%d\n", ft_atoi(av[1]));
}*/
