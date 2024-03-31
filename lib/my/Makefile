##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## task01
##

CC	=	gcc

NAME	=	libmy.a

SRC	=	my_put_nbr.c\
		my_putchar.c\
		my_putstr.c	\
		my_strcmp.c	\
		my_strcpy.c	\
		my_strdup.c	\
		my_strlen.c

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@cp libmy.a ../../

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME) ../../$(NAME)

re:	fclean all
