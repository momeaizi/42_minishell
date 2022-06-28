/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:36:01 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/27 11:56:59 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split(char ***tokens, char *s, char c)
{
	int		*size;
	int		j;
	int		i;

	j = 0;
	i = -1;
	size = tokens_length(s, c);
	*tokens = (char **)ft_calloc(count_tokens(s, c), sizeof(char *));
	if (!*tokens)
		return ;
	while (s[++i])
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
		{
			(*tokens)[j] = (char *)malloc(size[j] * sizeof(char));
			if (!(*tokens)[j])
				break ;
			ft_strlcpy((*tokens)[j], ((char *)s + i), size[j]);
			j++;
		}
	}
	free(size);
	if ((j + 1) != count_tokens(s, c))
		clear(*tokens, j);
	replace_all_strings(s, *tokens, c, -1);
}
