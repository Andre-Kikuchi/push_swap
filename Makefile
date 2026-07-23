NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
RM = rm -rf

SRCS = main.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)


clean:

fclean: clear
		$(RM) $(NAME)
		
re: fclean all

.PHONY: all clean fclean re