/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 19:03:04 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	update_map_elements(t_game *game, int i, int j)
{
	if (game->map.grid[i][j] == 'P')
	{
		game->map.player++;
		game->map.player_pos.x = j;
		game->map.player_pos.y = i;
	}
	else if (game->map.grid[i][j] == 'E')
		game->map.exit++;
	else if (game->map.grid[i][j] == 'C')
		game->map.collectibles++;
	else if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1')
		return (0);
	return (1);
}

int	check_map_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (!update_map_elements(game, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_borders(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if ((i == 0 || i == game->map.height - 1 || j == 0
					|| j == game->map.width - 1) && game->map.grid[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map_rectangular(t_game *game)
{
	int	i;
	int	width;

	width = ft_strlen(game->map.grid[0]);
	i = 1;
	while (i < game->map.height)
	{
		if ((int)ft_strlen(game->map.grid[i]) != width)
			return (0);
		i++;
	}
	game->map.width = width;
	return (1);
}
