/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:18:45 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/03 01:32:21 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_quotes(char *str)
{
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		j = 1;
		if (str[i] == '\"')
		{
			while (str[i + j] != '\"')
				j++;
			str[i] = -1;
			str[i + j] = -1;
			i += j;
		}
		else if (str[i] == '\'')
		{
			while (str[i + j] != '\'')
				j++;
			str[i] = -1;
			str[i + j] = -1;
			i += j;
		}
	}
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	i = -1;
	len = 0;
	replace_quotes(str);
	while (str[++i])
		if (str[i] == -1 || (str[i] == '$' && str[i + 1] == -1))
			len++;
	if (!len)
		return (replace(replace(str, -4, '\''), -5, '\"'));
	new_str = (char *)malloc((ft_strlen(str) - len + 1) * sizeof(char));
	if (!new_str)
		return (str);
	i = -1;
	j = 0;
	while (str[++i])
		if (!(str[i] == -1 || (str[i] == '$' && str[i + 1] == -1)))
			new_str[j++] = str[i];
	new_str[j] = 0;
	free(str);
	return (replace(replace(new_str, -4, '\''), -5, '\"'));
}
