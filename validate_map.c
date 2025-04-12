/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 19:00:31 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_elements_count(t_game *game)
{
	if (game->map.player != 1 || game->map.exit != 1
		|| game->map.collectibles < 1)
	{
		print_error("Map must have 1 player, 1 exit, and 1+ collectible.");
		free_map(&game->map);
		return (0);
	}
	return (1);
}

static int	validate_rectangular_and_borders(t_game *game)
{
	if (!check_map_rectangular(game))
	{
		print_error("Map is not rectangular.");
		free_map(&game->map);
		return (0);
	}
	if (!check_map_borders(game))
	{
		print_error("Map is not surrounded by walls.");
		free_map(&game->map);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!validate_rectangular_and_borders(game))
		return (0);
	if (!check_map_elements(game))
	{
		print_error("Map contains invalid characters.");
		free_map(&game->map);
		return (0);
	}
	if (!validate_elements_count(game))
		return (0);
	return (1);
}
