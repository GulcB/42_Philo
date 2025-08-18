NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread 
SRC = ./philo.c \
	./life_cycle.c \
	./utils.c \
	./cleanup.c \
	./dead.c \
	./init.c \
	./arg_ctrl.c \
	./sim_engine.c \
	./write_fd.c

all: ${NAME}

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re