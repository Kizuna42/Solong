/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:35:32 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_image(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	if (!img->img)
		print_error("Failed to load image");
}

int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("Failed to initialize MLX");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		print_error("Failed to create window");
		return (0);
	}
	return (1);
}

int	init_images(t_game *game)
{
	load_image(game, &game->wall, "textures/wall.xpm");
	load_image(game, &game->player, "textures/player.xpm");
	load_image(game, &game->collectible, "textures/collectible.xpm");
	load_image(game, &game->exit, "textures/exit.xpm");
	load_image(game, &game->floor, "textures/floor.xpm");
	if (!game->wall.img || !game->player.img || !game->collectible.img
		|| !game->exit.img || !game->floor.img)
	{
		print_error("Failed to load one or more images");
		return (0);
	}
	return (1);
}

int	init_game(t_game *game)
{
	if (!init_window(game))
	{
		free_map(&game->map);
		return (0);
	}
	if (!init_images(game))
	{
		free_map(&game->map);
		mlx_destroy_window(game->mlx, game->win);
		return (0);
	}
	return (1);
}
