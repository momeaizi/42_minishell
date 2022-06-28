NAME	= 	libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
 ft_strlcpy.c ft_strlcat.c skip_car.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c  ft_memcmp.c ft_strnstr.c \
 ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
 ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

BONUS	= ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c

SRCS_OBJS	:= $(SRCS:.c=.o)

BONUS_OBJS	:= $(BONUS:.c=.o)

OBJS	= $(SRCS_OBJS) $(BONUS_OBJS)

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address

.PHONY:	all clean fclean re bonus

all : $(NAME)

bonus : $(BONUS_OBJS)
	ar -rc libft.a $^

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
