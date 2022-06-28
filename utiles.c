/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 10:26:40 by mskerba           #+#    #+#             */
/*   Updated: 2022/06/27 07:10:26 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*join_readline_with_line(char *line)
{
	char	*buf;
	char	*new_line;

	buf = readline(">");
	if (!buf)
	{
		free(line);
		return (NULL);
	}
	new_line = ft_strjoin(line, buf);
	free(line);
	free(buf);
	return (new_line);
}
