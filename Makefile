# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 18:05:01 by momeaizi          #+#    #+#              #
#    Updated: 2022/07/05 21:28:32 by mskerba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = error.c main.c  utiles.c tokenizer.c unclosed_car.c create_list.c open_file.c\
	parser.c get_command.c get_env.c put_error.c clear.c exec.c\
	builtins/cd.c builtins/pwd.c builtins/env.c builtins/exit.c builtins/export.c builtins/echo.c builtins/unset.c builtins/builtins_utiles.c\
	expanding/expander.c expanding/init.c expanding/utils.c\
	quotes/is_there_any_quotes.c quotes/remove_quotes.c\
	split/split.c split/clear.c split/count_tokens.c split/tokens_length.c split/replace.c\
	
LDFLAGS=-L /goinfre/mskerba/.brew/opt/readline/lib
CPPFLAGS=-I /goinfre/mskerba/.brew/opt/readline/include

CC = cc

CFLAGS = $(LDFLAGS) $(CPPFLAGS) -lreadline  -Wall -Wextra -Werror  #-fsanitize=address

libft.a:
	@cd libft &&  make && make clean && mv libft.a ../

all: 
	@$(CC) $(CFLAGS) -L. libft.a $(SRC) -o minishell

fclean:
	@rm -rf libft.a

re: fclean libft.a all