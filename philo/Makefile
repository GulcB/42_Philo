NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread 
SRC = ./philo.c \
	./arg_ctrl.c \
	./check.c \
	./cleanup.c \
	./dead.c \
	./init.c \
	./life_cycle.c \
	./sim_engine.c \
	./utils.c \
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