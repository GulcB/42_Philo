NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread 
SRC = ./src/philo.c \
	./src/actions.c \
	./src/check_funcs.c \
	./src/cleanup.c \
	./src/dead.c \
	./src/init.c \
	./src/parsing.c \
	./src/simulation.c \
	./src/write_fd.c

all: ${NAME}

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re