NAME = Cub3D

CFLAGS = -Wall -Wextra -Werror  #Missing dans NAME et -c aussi

MINILIBX = -L ./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

SRC = main.c\

OBJ = main.o\

all: $(NAME)

$(NAME):
			@gcc -o $(NAME) $(SRC) $(MINILIBX)
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
