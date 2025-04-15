/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 16:20:47 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

# define MLX_ERROR 1
# define TILE_SIZE 32
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_vector	player_pos;
	int			player;
	int			exit;
	int			collectibles;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*exit;
	void	*collectible;
}	t_textures;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_textures	textures;
	int			moves;
	int			collected;
}	t_game;

// get_next_line.c
char	*get_next_line(int fd);

// utils.c
void	print_error(char *message);
void	free_map(t_map *map);
int		is_valid_file(char *filename);

// map_parser.c
int		parse_map(t_game *game, char *filename);

// validate_map.c
int		validate_map(t_game *game);

// map_path.c
int		check_map_path(t_game *game);

// map_parser_utils1.c
int		count_map_height(char *filename);
char	**read_map(char *filename, int height);

// map_parser_utils2.c
int		check_map_rectangular(t_game *game);
int		check_map_borders(t_game *game);
int		check_map_elements(t_game *game);

// map_parser_utils3.c
char	**create_map_copy(t_game *game);
int		flood_fill_recursive(char **map, int x, int y, int *collected);

// game_init.c
int		init_game(t_game *game);
int		init_mlx(t_game *game);
int		load_textures(t_game *game);

// game_loop.c
int		start_game(t_game *game);
int		key_press(int keycode, t_game *game);
int		close_game(t_game *game);

// game_movement.c
void	move_player(t_game *game, int x, int y);

// render.c
void	render_map(t_game *game);

#endif
