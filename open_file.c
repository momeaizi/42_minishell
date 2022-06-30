/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:35:17 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 15:09:27 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile(t_cmd *cmd, char *token, int index)
{
	char	*infile;
	int		fd;

	infile = remove_quotes(expand_var(ft_strdup(token), 0));
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
		else if (index > cmd->doc_index)
			cmd->in = fd;
	}
	free(infile);
}

void	open_outfile(t_cmd *cmd, char *token, int append)
{
	char	*outfile;
	int		fd;

	outfile = remove_quotes(expand_var(ft_strdup(token), 0));
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
