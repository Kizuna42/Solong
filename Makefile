# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kishino <kishino@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/04 22:41:36 by kishino           #+#    #+#              #
#    Updated: 2025/05/04 22:41:37 by kishino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long

CC			=	cc

FLAG		=	-Wall -Wextra -Werror

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

MLX_FILE	=	libmlx.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_FLAG	=	-lX11 -lXext

MLX_PATH	=	./minilibx-linux/

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

C_FILE		=	map.c				\
				map_checker.c		\
				render.c			\
				render_mouv.c		\
				set.c				\
				texture.c			\
				utils.c				\

SRC_DIR		=	./core/

INC_DIR		=	./includes/

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ			=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

lib:
	@make -C $(LIBFT_PATH)

mlx:
	@make -sC $(MLX_PATH)

$(NAME): lib mlx $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_EX) -o $(NAME)
	@echo "\033[1;32m./so_long created\n"

clean:
	@make clean -sC $(MLX_PATH)
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJ)
	@echo "\033[1;32mDone\n"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "\033[1;32mDone\n"

re: fclean all

.PHONY: all clean fclean re
