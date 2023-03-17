##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## initializes cat
##

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

OBJ2	=	*.o

COPIES	=	*~

COPIES2	=	#*#

NAME	=	my_sokoban

MAKE	=	make

LIB		=	./lib/my/libmy.a

CFLAGS	=	-g -lncurses

all:	princ clean

princ:	$(OBJ)
	cd ./lib/my/ && $(MAKE)
	gcc $(CFLAGS) -c $(SRC)
	rm -f my_printfdir/'*.o'
	gcc $(CFLAGS) $(OBJ) -o $(NAME) -L./lib/my -lmy

clean:
	rm -fr $(OBJ)
	rm -fr $(OBJ2)
	rm -fr $(COPIES)
	rm -fr $(COPIES2)

fclean:	clean
	rm -fr $(NAME)
	rm -fr $(LIB)

re:     fclean all
	rm -fr $(OBJ)
	rm -fr $(OBJ2)
