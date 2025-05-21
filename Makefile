# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/04 22:41:36 by kishino           #+#    #+#              #
#    Updated: 2025/05/21 15:26:47 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror

LIBFT_PATH	=	./libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_PATH	=	./minilibx-linux/
MLX_FILE	=	libmlx.a
MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))
MLX_FLAGS	=	-lX11 -lXext

SRC_DIR		=	./src/
INC_DIR		=	./includes/

SRC_FILES	=	map.c \
				map_checker.c \
				render.c \
				render_mouv.c \
				set.c \
				texture.c \
				utils.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

lib:
	@make -C $(LIBFT_PATH)

mlx:
	@make -sC $(MLX_PATH)

$(NAME): lib mlx $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;32m./so_long created\n"

clean:
	@make clean -sC $(MLX_PATH)
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJ)
	@echo "\033[1;32mClean done\n"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "\033[1;32mFclean done\n"

re: fclean all

.PHONY: all clean fclean re lib mlx
