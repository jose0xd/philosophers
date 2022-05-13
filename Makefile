CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = main.c utils.c
OBJ = $(SRC:.c=.o)

NAME = philo

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re bonus
