NAME	= 	libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
 ft_strlcpy.c ft_strlcat.c skip_car.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c  ft_memcmp.c ft_strnstr.c \
 ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c  ft_putchar_fd.c \
 ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c ft_realloc.c size_double.c add_spaces.c\


SRCS_OBJS	:= $(SRCS:.c=.o)

OBJS	= $(SRCS_OBJS)

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address

.PHONY:	all clean fclean re bonus

all : $(NAME)

libft.a : $(SRCS_OBJS)
	@echo "making libt" 
	@ar -rc $(NAME) $^

%.o	: %.c
	@cc $(CFLAGS) -c $^ -o $@

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
