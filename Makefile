#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/01/09 14:05:27 by psebasti          #+#    #+#             *#
#*   Updated: 2017/02/06 17:34:40 by psebasti         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME = fillit

SRC = main.c \
	  get_next_line.c \

OBJ		=	$(SRC:.c=.o)

CMP		=	gcc

FLAGS	=	-Wall -Wextra -Werror

LIB		=	-I /usr/X11/include -g -L libft/ -lft \
			/usr/X11/lib -l mlx -framework OpenGL -framework AppKit

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
