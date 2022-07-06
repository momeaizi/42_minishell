/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:24:57 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/06 15:26:46 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_from_heredoc(t_cmd *cmd, char *delimiter, char expand)
{
	char	*line;
	int		pipes[2];

	if (pipe(pipes) < 0)
		return ;
	if (cmd->in != 0)
		close(cmd->in);
	cmd->in = pipes[0];
	signal(SIGINT, &signal_handler);
	while (1)
	{
		line = readline("> ");
		if (expand && line)
			line = expand_var(line, 1);
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		write(pipes[1], line, ft_strlen(line));
		write(pipes[1], "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(pipes[1]);
	if (g_global.doc_exit)
		dup2(g_global.fd, 0);
}

void	open_heredocs(t_cmd *tmp, t_token ***tokens)
{
	char	*delimiter;
	int		j;
	int		i;

	i = -1;
	while (tokens[++i] && !g_global.doc_exit)
	{
		j = -1;
		while (tokens[i][++j] && !g_global.doc_exit)
		{
			if (tokens[i][j]->type == 4)
			{
				delimiter = remove_quotes(expand_var(\
				ft_strdup(tokens[i][j]->token), 0));
				tmp->doc_index = i;
				if (is_there_any_quote(tokens[i][j]->token))
					read_from_heredoc(tmp, delimiter, 0);
				else
					read_from_heredoc(tmp, delimiter, 1);
				free(delimiter);
				signal(SIGINT, &sig_handler);
			}
		}
		tmp = tmp->next;
	}
}

void	get_token_type(t_cmd *cmd, t_token *token, int j)
{
	int	size;

	if (!token->type)
	{
		size = size_double(cmd->args);
		cmd->args = ft_realloc(cmd->args, expand_var(\
		ft_strdup(token->token), 0));
		if (!ft_strlen(cmd->args[size]))
		{
			free(cmd->args[size]);
			cmd->args[size] = NULL;
		}
	}
	else if (token->type == 1)
		open_infile(cmd, token->token, remove_quotes(\
		expand_var(ft_strdup(token->token), 0)), j);
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

	tmp = g_global.cmds;
	open_heredocs(tmp, tokens);
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
