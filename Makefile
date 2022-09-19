# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskerba <mskerba@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 18:05:01 by momeaizi          #+#    #+#              #
#    Updated: 2022/09/19 21:18:37 by mskerba          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  main.c\
	utiles/utiles.c utiles/clear.c   utiles/create_list.c \
	parcing/parser.c parcing/tokenizer.c  parcing/open_file.c\
	execution/get_command.c execution/get_env.c execution/exec.c\
	error/error.c error/unclosed_car.c error/put_error.c\
	builtins/cd.c builtins/pwd.c builtins/env.c builtins/exit.c builtins/export.c builtins/echo.c builtins/unset.c builtins/builtins_utiles.c\
	expanding/expander.c expanding/init.c expanding/utils.c\
	quotes/is_there_any_quotes.c quotes/remove_quotes.c\
	split/split.c split/clear.c split/count_tokens.c split/tokens_length.c split/replace.c\
	wildcards/wildcards.c wildcards/willdcards_check.c   minishell.c 

LDFLAGS= -L /Users/mskerba/goinfre/.brew/opt/readline/lib
CPPFLAGS= -I /Users/mskerba/goinfre/.brew/opt/readlin/include

NAME=minishell
LIB=libft.a

OBJS:=$(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror $(HEADERS) -fsanitize=address
all: $(LIB) $(NAME)

$(LIB):
	cd libft &&  make && make clean && mv $(LIB) ../


$(NAME): $(OBJS) 
	$(CC)  -lreadline $(CFLAGS) $(OBJS) -L. $(LIB) -o $(NAME)

clean :
	rm -f $(OBJS) $(LIB)

fclean: clean
	rm -rf $(NAME)

re: fclean all