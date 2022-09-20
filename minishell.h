/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:59:43 by momeaizi          #+#    #+#             */
/*   Updated: 2022/09/20 20:32:46 by momeaizi         ###   ########.fr       */
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
	int		exit_code;
	int		doc_exit;
	int		fd;
}					t_global;

t_global	g_global;

void	open_outfile(t_cmd *cmd, char *token, char **outfile, int append);
void	replace_all_strings(char *str, char **strs, char new, char old);
void	open_infile(t_cmd *cmd, char *token, char **infile, int index);
void	replace_inside_quotes(char *str, char new, char old);
void	put_error_two(char *str, char *idt, char *error);
void	parse_execute(char *line, t_token ***tokens);
char	**asterisk(char *arg, char **args, int size);
int		skip_quotes(char *line, int i, char quote);
char	*get_cmd_path(t_cmd *cmd, char *cmd_name);
int		first_char(char *arg, char *dir_content);
char	*replace(char *str, char old, char new);
int		last_char(char *arg, char *dir_content);
char	*expand_var(char *str, char expand_all);
int		wildcards(char *arg, char *dir_content);
void	minishell(int flag, t_token ***tokens);
void	split(char ***tokens, char *s, char c);
char	*get_path(t_cmd *cmd, char *cmd_name);
char	*join_readline_with_line(char *line);
int		filter(char *arg, char *dir_content);
int		check_env_var(t_cmd *cmd, char *env);
void	change_env_var(char *var, char *val);
void	exec(t_cmd *tmp, int *pid, int i);
int		*tokens_length(char *str, char c);
void	put_error(char *str, char *error);
int		skip_brackets(char *line, int i);
char	**split_spaces(char *s, char c);
int		count_tokens(char *str, char c);
void	clear_tokens(t_token ***tokens);
int		is_there_any_quote(char *str);
int		skip_space(char *line, int i);
int		valid_parentheses(char *line);
void	clear_all(t_token ***tokens);
void	we_unset(char *var_to_unset);
void	clear(char **paths, int j);
void	clear_triple(char ***cmds);
int		is_all_asterisk(char *arg);
void	parser(t_token ***tokens);
char	*remove_quotes(char *str);
char	*get_next_cmd(char *line);
void	print_export(t_cmd *cmd);
int		size_double(char **cmds);
char	*unclosed_brackets(void);
int		is_duplicated(char *var);
void	signal_handler(int sig);
int		is_operator(char *line);
int		get_var_len(char *str);
int		list_size(t_cmd *cmds);
char	*unclosed_quotes(void);
char	**copy_env(char **env);
void	close_all(t_cmd *cmd);
char	*ft_getenv(char *var);
void	create_list(int size);
void	ft_export(t_cmd *cmd);
void	remove_tab(char *str);
char	*get_cmd(char *line);
char	*get_var(char *args);
char	*get_val(char *args);
t_token	***lexer(char *line);
void	ft_unset(t_cmd *cmd);
char	*get_var(char *args);
void	sig_handler(int sig);
char	*get_val(char *args);
void	ft_echo(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
int		check_error(void);
void	ft_cd(t_cmd *cmd);
void	clear_cmds(void);
int		abs(int n);

#endif
