/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 07:34:22 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 12:37:44 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	while (1)
	{
		g_global.line = readline("minishell> ");
		add_history(g_global.line);
		if (!check_error())
			continue ;
		if (!g_global.line || !ft_strlen(g_global.line))
			continue ;
		if (g_global.line)
			g_global.line = add_spaces(g_global.line);
		lexer(g_global.line);
		free(g_global.line);
		system("leaks minishell");
	}
}
