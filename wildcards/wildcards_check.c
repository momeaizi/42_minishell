/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 07:38:11 by mskerba           #+#    #+#             */
/*   Updated: 2022/08/30 15:07:16 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_char(char *arg)
{
    int i;

    i = -1;
    while (arg[++i])
        if(arg[i] != '*')
            return (0);
    return (1);
}

int check_end(char *arg, char *dir_content)
{
    if (arg[ft_strlen(arg) - 1] != dir_content[ft_strlen(dir_content) - 1] && arg[ft_strlen(arg) - 1] != '*')
        return (0);

    return (1);
}

int check_start(char *arg, char *dir_content)
{
    if (arg[0] != dir_content[0] && arg[0] != '*')
        return (0);
    return (1);
}

int check_all(char *arg, char *dir_content)
{
    int i;
    int j;


    i = -1;
    j = -1;
    while (arg[++i])
    {
        if (arg[i] != '*')
        {
            while(1)
            {
                if (!dir_content[j])
                    return (0);
                else if (dir_content[++j] == arg[i])
                    break;
            }
        }
    }
    return (1);
}