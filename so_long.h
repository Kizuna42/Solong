/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:33:57 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "minilibx_opengl_20191021/mlx.h"

# define TILE_SIZE 32
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exit;
	int		player;
	t_pos	player_pos;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	wall;
	t_img	player;
	t_img	collectible;
	t_img	exit;
	t_img	floor;
	int		moves;
	int		collected;
}	t_game;

/* main.c */
int		main(int argc, char **argv);

/* map_parser.c */
int		parse_map(t_game *game, char *filename);
int		validate_map(t_game *game);
int		check_map_path(t_game *game);

/* game_init.c */
int		init_game(t_game *game);
int		init_images(t_game *game);
int		init_window(t_game *game);

/* game_loop.c */
int		game_loop(t_game *game);
int		key_press(int keycode, t_game *game);
int		close_game(t_game *game);

/* render.c */
void	render_map(t_game *game);
void	put_image(t_game *game, void *img, int x, int y);

/* utils.c */
void	free_map(t_map *map);
void	print_error(char *msg);
int		is_valid_file(char *filename);

#endif
