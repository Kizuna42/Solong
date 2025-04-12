/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:58:43 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_texture(t_game *game, void **texture, char *path)
{
	int	width;
	int	height;

	*texture = mlx_xpm_file_to_image(game->mlx.mlx, path, &width, &height);
	if (!*texture)
		print_error("Failed to load texture");
}

int	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		print_error("Failed to initialize MLX");
		return (0);
	}
	game->mlx.win = mlx_new_window(game->mlx.mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");
	if (!game->mlx.win)
	{
		print_error("Failed to create window");
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	load_texture(game, &game->textures.wall, "textures/wall.xpm");
	load_texture(game, &game->textures.player, "textures/player.xpm");
	load_texture(game, &game->textures.collectible, "textures/collectible.xpm");
	load_texture(game, &game->textures.exit, "textures/exit.xpm");
	load_texture(game, &game->textures.floor, "textures/floor.xpm");
	if (!game->textures.wall || !game->textures.player
		|| !game->textures.collectible || !game->textures.exit
		|| !game->textures.floor)
	{
		print_error("Failed to load one or more textures");
		return (0);
	}
	return (1);
}

int	init_game(t_game *game)
{
	if (!init_mlx(game))
	{
		free_map(&game->map);
		return (0);
	}
	if (!load_textures(game))
	{
		free_map(&game->map);
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		return (0);
	}
	return (1);
}
