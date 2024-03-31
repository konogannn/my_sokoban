##
## EPITECH PROJECT, 2023
## my_sokoban
## File description:
## Makefile
##

CC	=	gcc

TARGET	=	my_sokoban

UNIT_TESTS	=	unit_tests

CFLAGS	=	-Wall -Wextra -Wshadow -I./include

LDFLAGS	=	-L. -lmy  -lncurses

CRITERIONFLAGS	=	--coverage -lcriterion

SRC	=	src/display.c		\
		src/init.c			\
		src/main.c			\
		src/my_prog.c		\
		src/my_sokoban.c	\
		src/open_map.c		\
		src/win_cond.c

BONUS =	bonus/display.c		\
		$(filter-out src/display.c, $(SRC))

SRCTEST	=	$(filter-out src/main.c, $(SRC))

FILETEST	=	tests/unit_test.c

OBJ	=	$(SRC:.c=.o)
BOBJ	=	$(BONUS:.c=.o)

.PHONY: all clean fclean  norme re tests_run

all: $(TARGET)

$(TARGET):	$(OBJ)
	@echo -e "\e[1m\e[36mBuilding $(TARGET)...\e[0m"
	@$(MAKE) -C ./lib/my -lmy > /dev/null 2>&1
	@$(CC) -o $(TARGET) $(OBJ) $(CFLAGS) $(LDFLAGS)
	@echo -e "\e[1m\e[32mBinary ready!\e[0m"

bonus: $(BOBJ)
	@echo -e "\e[36mBuilding bonus...\e[0m"
	@$(MAKE) -C ./lib/my > /dev/null 2>&1
	@$(CC) -o $(TARGET) $(BOBJ) $(CFLAGS) $(LDFLAGS)
	@echo -e "\e[1m\e[32mBonus ready:)\e[0m"

$(UNIT_TESTS):	fclean
	@$(MAKE) -C ./lib/my > /dev/null 2>&1
	@$(CC) -o $(UNIT_TESTS) $(SRCTEST) $(FILETEST) $(LDFLAGS) \
	$(CRITERIONFLAGS)

tests_run:	$(UNIT_TESTS)
	@./$(UNIT_TESTS)
	@gcovr --exclude tests/

norme: fclean
	@coding-style . .
	@cat coding-style-reports.log
	@rm -f coding-style-reports.log

clean:
	@$(MAKE) clean -C ./lib/my > /dev/null 2>&1
	@rm -f $(OBJ)
	@rm -f $(BOBJ)
	@rm -f *.gc*
	@rm -f coding-style-reports.log

fclean: clean
	@$(MAKE) fclean -C ./lib/my > /dev/null 2>&1
	@rm -f $(TARGET)
	@rm -f $(UNIT_TESTS)

re: fclean all
