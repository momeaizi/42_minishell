/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 10:54:51 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 11:02:24 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	need_space(char *line, int i)
{
	if (i && (line[i] == '>' || line[i] == '<') && line[i - 1] != line[i])
		return (1);
	else if (i && (line[i - 1] == '>' || line[i - 1] == '<') && line[i
			- 1] != line[i])
		return (1);
	return (0);
}

static int	count_redirection(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (line[++i])
		if ((line[i] == '>' || line[i] == '<') && line[i + 1] != line[i])
			count++;
	return (count);
}

char	*add_spaces(char *line)
{
	char	*new_line;
	int		count;
	int		i;
	int		j;

	j = 0;
	i = -1;
	count = count_redirection(line);
	new_line = malloc(sizeof(char *) * ((count * 2) + strlen(line) + 1));
	while (line[++i])
	{
		if (need_space(line, i))
		{
			new_line[j] = ' ';
			j++;
		}
		new_line[j] = line[i];
		j++;
	}
	new_line[j] = 0;
	free(line);
	return (new_line);
}
