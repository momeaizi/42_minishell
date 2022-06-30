/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:24:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/30 12:32:06 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT)
		exit(1);
}

void	read_from_heredoc(t_cmd *cmd, char *delimiter)
{
	char	*line;
	int		pipes[2];
	int		id;

	if (pipe(pipes) < 0)
		return ;
	cmd->in = pipes[0];
	id = fork();
	if (id)
		return ;
	signal(SIGINT, &heredoc_signal);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (!ft_strcmp(line, delimiter))
			break ;
		write(pipes[1], line, ft_strlen(line));
		write(pipes[1], "\n", 1);
		free(line);
	}
	free(line);
	free(delimiter);
	exit(0);
}

void	open_heredocs(t_token ***tokens)
{
	t_cmd	*tmp;
	int		j;
	int		i;

	tmp = g_global.cmds;
	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j] && !g_global.doc_exit)
		{
			if (tokens[i][j]->type == 4)
			{
				tmp->doc_index = i;
				read_from_heredoc(tmp, remove_quotes(expand_var(ft_strdup(tokens[i][j]->token), 0)));
				wait(&g_global.doc_exit);
			}
		}
		tmp = tmp->next;
	}
}

void	parser(t_token ***tokens)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	open_heredocs(tokens);
	tmp = g_global.cmds;
	i = -1;
	while (tokens[++i])
	{
		j = -1;
		while (tokens[i][++j] && !tmp->error)
		{
			if (!tokens[i][j]->type)
			{
				tmp->args = ft_realloc(tmp->args, remove_quotes(expand_var(ft_strdup(tokens[i][j]->token), 0)));
				if (!tmp->args[0])
					tmp->path = get_cmd_path(tmp->args[size_double(tmp->args) - 1]);
			}
			else if (tokens[i][j]->type == 1)
				open_infile(tmp, tokens[i][j]->token, i);
			else if (tokens[i][j]->type == 2)
				open_outfile(tmp, tokens[i][j]->token, 0);
			else if (tokens[i][j]->type == 3)
				open_outfile(tmp, tokens[i][j]->token, 1);
		}
		tmp = tmp->next;
	}
}
