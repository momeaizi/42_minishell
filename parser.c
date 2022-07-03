/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:24:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/03 15:30:32 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	heredoc_signal(int sig)
{
	write(1, "\n", 1);
	if (sig == SIGINT)
		exit(1);
}

void	read_from_heredoc(t_cmd *cmd, char *delimiter, char expand)
{
	char	*line;
	int		pipes[2];
	int		id;

	if (pipe(pipes) < 0)
		return ;
	if (cmd->in != 0)
		close(cmd->in);
	cmd->in = pipes[0];
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (!id)
	{
		signal(SIGINT, &heredoc_signal);
		while (1)
		{
			line = readline("> ");
			if (expand)
				line = expand_var(line, 1);
			if (!line || !ft_strcmp(line, delimiter))
			{
				if (line)
					free(line);
				close(pipes[0]);
				close(pipes[1]);
				break ;
			}
			write(pipes[1], line, ft_strlen(line));
			write(pipes[1], "\n", 1);
			free(line);
		}
		exit(0);
	}
	else
	{
		close(pipes[1]);
		return ;
	}
}

void	open_heredocs(t_token ***tokens)
{
	char	*delimiter;
	t_cmd	*tmp;
	int		j;
	int		i;

	tmp = g_global.cmds;
	i = -1;
	while (tokens[++i] && !g_global.doc_exit)
	{
		j = -1;
		while (tokens[i][++j] && !g_global.doc_exit)
		{
			if (tokens[i][j]->type == 4)
			{
				delimiter = remove_quotes(expand_var(ft_strdup(tokens[i][j]->token), 0));
				tmp->doc_index = i;
				if (is_there_any_quote(tokens[i][j]->token))
					read_from_heredoc(tmp, delimiter, 0);
				else
					read_from_heredoc(tmp, delimiter, 1);
				wait(&g_global.doc_exit);
				g_global.doc_exit = WEXITSTATUS(g_global.doc_exit);
				free(delimiter);
			}
		}
		tmp = tmp->next;
	}
}

void	get_token_type(t_cmd *cmd, t_token *token, int j)
{
	if (!token->type)
	{
		cmd->args = ft_realloc(cmd->args, remove_quotes(\
		expand_var(ft_strdup(token->token), 0)));
		if (!cmd->args[1])
			cmd->path = get_cmd_path(cmd->args[0]);
	}
	else if (token->type == 1)
		open_infile(cmd, token->token, j);
	else if (token->type == 2)
		open_outfile(cmd, token->token, remove_quotes(\
		expand_var(ft_strdup(token->token), 0)), 0);
	else if (token->type == 3)
		open_outfile(cmd, token->token, remove_quotes(\
		expand_var(ft_strdup(token->token), 0)), 1);
}

void	parser(t_token ***tokens)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	open_heredocs(tokens);
	tmp = g_global.cmds;
	i = -1;
	while (tokens[++i] && !g_global.doc_exit)
	{
		j = -1;
		while (tokens[i][++j] && !tmp->error && !g_global.doc_exit)
		{
			get_token_type(tmp, tokens[i][j], j);
		}
		tmp = tmp->next;
	}
}
