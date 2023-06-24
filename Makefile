CC = gcc
CFLAG = -Wall -Wextra -Werror
SRC = hangman.c get_next_line.c get_next_line_utils.c
OUTPUT = -o
NAME = hangman
OBJ = $(src:.c=.o) 


all:$(NAME)
	./hangman

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(SRC) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
