/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:35:17 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 17:07:58 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(char *str, char *error)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	open_infile(t_cmd *cmd, char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		put_error(infile, strerror(errno));
		cmd->error = 1;
	}
	else
	{
		if (cmd->in != 0)
			close(cmd->in);
		cmd->in = fd;
	}
}

void	open_outfile(t_cmd *cmd, char *outfile, int append)
{
	int	fd;

	if (!append)
		fd = open(outfile, O_WRONLY | O_CREAT, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		put_error(outfile, strerror(errno));
		cmd->error = 1;
	}
	else
	{
		if (cmd->out != 1)
			close(cmd->out);
		cmd->out = fd;
	}
}
