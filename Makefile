##
## EPITECH PROJECT, 2021
## makefile
## File description:
## makefile
##

NAME = myftp

SRC = *.c

FLAGS = -Wall -Wextra -g3

all:
	gcc -o $(NAME) $(SRC) $(FLAGS)

clean:
	rm -f *~ | rm -f *.o

fclean: clean
	rm -f $(NAME)

re:	fclean all
