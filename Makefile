# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momeaizi <momeaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 18:05:01 by momeaizi          #+#    #+#              #
#    Updated: 2022/06/28 18:54:04 by momeaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = error.c main.c  utiles.c tokenizer.c unclosed_car.c create_list.c open_file.c\
	parser.c\
	split/split.c split/clear.c split/count_tokens.c split/tokens_length.c split/replace.c\
	
 
CC = cc

CFLAGS = -lreadline -Wall -Wextra -Werror -fsanitize=address

libft.a:
	@cd libft &&  make && make clean && mv libft.a ../

all: 
	@$(CC) $(CFLAGS) -L. libft.a $(SRC) -o minishell

fclean:
	@rm -rf libft.a

re: fclean libft.a all 
	