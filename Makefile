NAME = 			Rubik

OBJ_DIR  =		./obj/

SRC_DIR =	./src/
SRC = 		main.cpp

SRCS      =	$(addprefix $(SRC_DIR), $(SRC))

OBJ  =	$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

CC = g++ #-Wall -Wextra -Werror -Wuninitialized
CFLAGS  = -I ./inc/

####################_OPTIONS_########################
DINO=0
STYLE=1
CLEANSONORE=1
#####################################################

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@printf " _/\nRubik  [done]\n"

clean:
	@rm -f $(OBJ)
	@printf "clean  [done]\n"

fclean: clean
	@rm -f $(NAME)
	@printf "fclean [done]\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@printf ">"
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

re: fclean all

.PHONY: all clean fclean re $(NAME)