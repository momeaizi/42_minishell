/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:59:43 by momeaizi          #+#    #+#             */
/*   Updated: 2022/06/28 18:53:18 by momeaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_token
{
	char			*token;
	int				type;
}					t_token;

# define ARG 0
# define IN 1
# define OUT 2
# define OUT_APP 3
# define HEREDOC 4

typedef struct s_cmd
{
	int				in;
	int				out;
	int				error;
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_global
{
	char			*line;
	char			**env;
	t_cmd			*cmds;
}					t_global;

t_global	g_global;

void	replace_all_strings(char *str, char **strs, char new, char old);
void	replace_inside_quotes(char *str, char new, char old);
void	open_outfile(t_cmd *cmd, char *outfile, int append);
int		skip_quotes(char *line, int i, char quote);
char	*replace(char *str, char old, char new);
void	split(char ***tokens, char *s, char c);
void	open_infile(t_cmd *cmd, char *infile);
char	*join_readline_with_line(char *line);
int		*tokens_length(char *str, char c);
char	**split_spaces(char *s, char c);
int		count_tokens(char *str, char c);
int		skip_space(char *line, int i);
void	clear(char **paths, int j);
void	clear_triple(char ***cmds);
void	parser(t_token ***tokens);
int		skip_brackets(char *line);
int		size_double(char **cmds);
char	*unclosed_brackets(void);
char	*unclosed_quotes(void);
void	create_list(int size);
t_cmd	*lexer(char *line);
int		check_error(void);
int		abs(int n);

#endif