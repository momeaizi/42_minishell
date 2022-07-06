/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:35:32 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/06 14:48:51 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_error(char *str, char *error)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	put_error_two(char *str, char *idt, char *error)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, idt, ft_strlen(idt));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
