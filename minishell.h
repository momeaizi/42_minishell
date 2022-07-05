/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:59:43 by momeaizi          #+#    #+#             */
/*   Updated: 2022/07/05 22:02:00 by mskerba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

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
	int				doc_index;
	char			*path;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_global
{
	t_cmd	*cmds;
	char	*line;
	char	**env;
	int		error;
	int		doc_exit;
	int		fd;
}					t_global;

t_global	g_global;

void	open_outfile(t_cmd *cmd, char *token, char *outfile, int append);
void	replace_all_strings(char *str, char **strs, char new, char old);
void	open_infile(t_cmd *cmd, char *token, char *infile, int index);
void	replace_inside_quotes(char *str, char new, char old);
void	put_error_two(char *str, char *idt, char *error);
int		skip_quotes(char *line, int i, char quote);
char	*get_cmd_path(t_cmd *cmd, char *cmd_name);
char	*replace(char *str, char old, char new);
char	*expand_var(char *str, char expand_all);
void	split(char ***tokens, char *s, char c);
char	*get_path(t_cmd *cmd, char *cmd_name);
char	*join_readline_with_line(char *line);
int		check_env_var(t_cmd *cmd, char *env);
void	change_env_var(char *var, char *val);
int		*tokens_length(char *str, char c);
void	put_error(char *str, char *error);
char	**split_spaces(char *s, char c);
int		count_tokens(char *str, char c);
void	clear_tokens(t_token ***tokens);
int		is_there_any_quote(char *str);
int		skip_space(char *line, int i);
void	we_unset(char *var_to_unset);
void	clear(char **paths, int j);
void	clear_triple(char ***cmds);
void	parser(t_token ***tokens);
char	*remove_quotes(char *str);
int		skip_brackets(char *line);
void	print_export(t_cmd *cmd);
int		size_double(char **cmds);
char	*unclosed_brackets(void);
int		is_duplicated(char *var);
void	signal_handler(int sig);
int		list_size(t_cmd *cmds);
char	*unclosed_quotes(void);
void	close_all(t_cmd *cmd);
char	**copy_env(char **env);
char	*ft_getenv(char *var);
void	create_list(int size);
int		ft_export(t_cmd *cmd);
char	*get_var(char *args);
char	*get_val(char *args);
t_token	***lexer(char *line);
int		ft_unset(t_cmd *cmd);
char	*get_var(char *args);
void	sig_handler(int sig);
char	*get_val(char *args);
int		ft_echo(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		check_error(void);
int		ft_cd(t_cmd *cmd);
void	clear_cmds(void);
void	exec(void);
int		abs(int n);

#endif
