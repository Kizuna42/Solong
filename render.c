/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:58:30 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, img, x * TILE_SIZE,
		y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			put_image(game, game->textures.floor, j, i);
			if (game->map.grid[i][j] == '1')
				put_image(game, game->textures.wall, j, i);
			else if (game->map.grid[i][j] == 'P')
				put_image(game, game->textures.player, j, i);
			else if (game->map.grid[i][j] == 'C')
				put_image(game, game->textures.collectible, j, i);
			else if (game->map.grid[i][j] == 'E')
				put_image(game, game->textures.exit, j, i);
			j++;
		}
		i++;
	}
}
