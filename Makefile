CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = main.c utils.c init.c
OBJ = $(SRC:.c=.o)

NAME = philo

$(NAME): $(OBJ) philo.h
	$(CC) $(OBJ) -o $(NAME) -pthread

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re bonus
