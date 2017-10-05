#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/01/09 14:05:27 by psebasti          #+#    #+#             *#
#*   Updated: 2017/10/05 13:27:12 by psebasti         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = fdf

SRC 		=	src/fdf.c \
				src/color.c \
				src/draw.c \
				src/draw_line.c \
				src/cam.c \
				src/mlx_process.c \
				src/read_map.c \
				src/parsing.c \
				src/setup.c \
				src/setup_delete.c \
				src/update_map.c \
				src/configure_map.c \
				src/configure_map_dim.c \
				src/setup_gen.c \
				src/save_map.c \

EXT			=	Makefile

OBJ			=	$(SRC:.c=.o)

CMP			=	gcc

FLAGS		=	-ggdb -Wall -Wextra -Werror

LIB_DIR		=	-L libs/libft/ -L libs/libft/minilibx
LIBS		=	-lft -lmlx -framework OpenGL -framework AppKit

all : lib $(NAME)

$(NAME) : $(OBJ) $(EXT)
	@$(CMP) $(FLAGS) -o $(NAME) $(SRC) $(LIB_DIR) $(LIBS)
	@echo "fdf compiled"

lib :
	@echo "compiling libft..."
	@make -C libs/libft/ --no-print-directory
	@echo "libft compiled"
	@echo "compiling mlx..."
	@make -C libs/libft/minilibx/ --no-print-directory
	@echo "mlx compiled"

clean :
	@rm -f $(OBJ)
	@echo "cleaning libft..."
	@make -C libs/libft/ clean --no-print-directory
	@echo "cleaning mlx..."
	@make -C libs/libft/minilibx/ clean --no-print-directory
	@echo "clean done"

fclean : clean
	@rm -f $(NAME)
	@echo "full cleaning libft..."
	@make -C libs/libft/ fclean --no-print-directory
	@echo "fclean done"

re : fclean all

.PHONY: $(NAME) all clean fclean re
