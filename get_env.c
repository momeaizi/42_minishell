/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:59:28 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/29 10:39:26 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(var);
	while (g_global.env[++i])
		if (!ft_strncmp(g_global.env[i], var, len) \
		&& g_global.env[i][len] == '=')
			return (ft_strdup(g_global.env[i] + len + 1));
	return (NULL);
}
