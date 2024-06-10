NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -O2 -pthread #-fsanitize=thread

SRCS		= main.c \
					parse.c \
					eat.c \
					errors.c \
					init.c \
					destroy.c \
					routine.c \
					start.c \
					state.c \
					time.c

OBJS		= $(SRCS:.c=.o)

# BUILD

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all
