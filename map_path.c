/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:55:30 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_invalid_path(t_game *game)
{
	print_error("No valid path found in map.");
	free_map(&game->map);
	return (0);
}

int	check_map_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		collected;
	int		exit_found;

	map_copy = create_map_copy(game);
	if (!map_copy)
		return (0);
	collected = 0;
	exit_found = flood_fill_recursive(map_copy, game->map.player_pos.x,
			game->map.player_pos.y, &collected);
	i = 0;
	while (i < game->map.height)
		free(map_copy[i++]);
	free(map_copy);
	if (!exit_found || collected != game->map.collectibles)
		return (handle_invalid_path(game));
	return (1);
}
