# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#              #
#    Updated: 2025/04/15 16:16:16 by kizuna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = main.c \
		map_parser.c \
		game_init.c \
		game_loop.c \
		render.c \
		utils.c \
		map_parser_utils1.c \
		map_parser_utils2.c \
		map_parser_utils3.c \
		validate_map.c \
		map_path.c \
		game_movement.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# 環境に応じてMLXライブラリを選択
ifeq ($(shell uname), Darwin)
    MLX_DIR = minilibx_opengl_20191021
    MLX_LIBS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
    MLX_DIR = minilibx-linux
    MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11
endif

MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS = -L$(LIBFT_DIR) -lft $(MLX_LIBS)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@echo "Compiling libft library"
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "Compiling MLX library"
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
