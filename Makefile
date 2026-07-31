NAME		= push_swap
BONUS_NAME	= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c ops.c parse.c parse_nums.c disorder.c \
			  stack.c utils.c utils2.c bench.c \
			  sort_complex.c sort_medium.c sort_simple.c sort_small.c

BONUS_SRCS	= checker_bonus.c ops.c parse.c parse_nums.c disorder.c \
			  stack.c utils.c utils2.c bench.c \
			  sort_complex.c sort_medium.c sort_simple.c sort_small.c


OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re