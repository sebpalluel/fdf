#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/01/09 14:05:27 by psebasti          #+#    #+#             *#
#*   Updated: 2017/02/07 21:23:24 by psebasti         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = fdf

SRC =		src/fdf.c \
			get_next_line/get_next_line.c \

OBJ		=	$(SRC:.c=.o)

CMP		=	gcc

FLAGS	=	-Wall -Wextra -Werror

LIB		=	-L libft/ -lft -L./mlx \
			-lmlx -framework OpenGL -framework AppKit

all : lib $(NAME)

$(NAME) :
	@$(CMP) $(FLAGS) -o $(NAME) $(SRC) $(LIB)
	@echo "fdf compiled"

lib :
	@make re -C libft
	@echo "libft compiled"

clean :
	@rm -rf $(OBJ)
	@make -C libft clean
	@echo "clean done"

fclean : clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@echo "fclean done"

re : fclean all

.PHONY: $(NAME) all clean fclean re
