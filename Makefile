# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kishino <kishino@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/21 15:39:19 by kishino           #+#    #+#              #
#    Updated: 2025/05/21 15:39:57 by kishino          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR)

LIBFT_PATH	= ./libft/
LIBFT_FILE	= libft.a
LIBFT_LIB	= $(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_PATH	= ./minilibx-linux/
MLX_FILE	= libmlx.a
MLX_LIB		= $(addprefix $(MLX_PATH), $(MLX_FILE))
MLX_FLAGS	= -lX11 -lXext

SRC_DIR		= ./src/
INC_DIR		= ./includes/

SRC_FILES	= map.c \
			map_checker.c \
			render.c \
			render_mouv.c \
			set.c \
			texture.c \
			utils.c

SRC		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ		= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

lib:
	@make -C $(LIBFT_PATH)

mlx:
	@make -sC $(MLX_PATH)

$(NAME): lib mlx $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

clean:
	@make clean -sC $(MLX_PATH)
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re lib mlx
