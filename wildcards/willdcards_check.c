/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   willdcards_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 07:38:11 by mskerba           #+#    #+#             */
/*   Updated: 2022/09/06 13:50:17 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_all_asterisk(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (arg[i] != '*')
			return (0);
	return (1);
}

int	last_char(char *arg, char *dir_content)
{
	int	i;
	int	j;

	i = ft_strlen(arg) - 1;
	j = ft_strlen(dir_content) - 1;
	if (dir_content[j] == (arg[i] + 49))
		return (1);
	if (arg[i] != dir_content[j] && arg[i] != '*')
		return (0);
	return (1);
}

int	first_char(char *arg, char *dir_content)
{
	if (dir_content[0] == (arg[0] + 49))
		return (1);
	if (arg[0] != dir_content[0] && arg[0] != '*')
		return (0);
	return (1);
}

int	filter(char *arg, char *dir_content)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (arg[++i])
	{
		if (arg[i] != '*')
		{
			while (1)
			{
				if (!dir_content[++j])
					return (0);
				else if (dir_content[j] == arg[i] || \
				dir_content[j] == (arg[i] + 49))
				{
					if (arg[i + 1] != '*' && dir_content[j + 1] != arg[i + 1] \
					&& dir_content[j + 1] != (arg[i + 1] + 49))
						return (0);
					break ;
				}
			}
		}
	}
	return (1);
}
