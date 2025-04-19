# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#              #
#    Updated: 2025/04/19 18:48:41 by kizuna           ###   ########.fr        #
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

# Linux環境用のMLXライブラリ設定
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS = -L$(LIBFT_DIR) -lft $(MLX_LIBS)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@echo "Compiling libft library"
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "Compiling MLX library for Linux"
	cd $(MLX_DIR) && ./configure
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
