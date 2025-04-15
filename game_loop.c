/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 16:26:40 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_textures(t_game *game)
{
	if (game->textures.wall)
		mlx_destroy_image(game->mlx.mlx, game->textures.wall);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx.mlx, game->textures.floor);
	if (game->textures.player)
		mlx_destroy_image(game->mlx.mlx, game->textures.player);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx.mlx, game->textures.exit);
	if (game->textures.collectible)
		mlx_destroy_image(game->mlx.mlx, game->textures.collectible);
}

int	close_game(t_game *game)
{
	free_textures(game);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	free_map(&game->map);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	render_map(game);
	return (0);
}

int	start_game(t_game *game)
{
	render_map(game);
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 17, 0, close_game, game);
	mlx_loop(game->mlx.mlx);
	return (0);
}
