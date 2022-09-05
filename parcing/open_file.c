/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:35:17 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/04 16:13:21 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_infile(t_cmd *cmd, char *token, char *infile, int index)
{
	int	fd;

	if (!ft_strlen(infile) && ft_strlen(token))
	{
		put_error(token, "ambiguous redirect");
		free(infile);
		cmd->error = 1;
		return ;
	}
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		put_error(infile, strerror(errno));
		cmd->error = 1;
	}
	else
	{
		if (cmd->in != 0 && index > cmd->doc_index)
			close(cmd->in);
		if (index > cmd->doc_index)
			cmd->in = fd;
		else
			close(fd);
	}
	free(infile);
}

void	open_outfile(t_cmd *cmd, char *token, char *outfile, int append)
{
	int		fd;

	if (!ft_strlen(outfile) && ft_strlen(token))
	{
		put_error(token, "ambiguous redirect");
		free(outfile);
		cmd->error = 1;
		return ;
	}
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
	free(outfile);
}
