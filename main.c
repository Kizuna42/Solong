/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:11:32 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_map_values(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->player = 0;
	map->exit = 0;
	map->collectibles = 0;
	map->grid = NULL;
}

static void	init_game_values(t_game *game)
{
	init_map_values(&game->map);
	game->moves = 0;
	game->collected = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./so_long <map_file.ber>");
		return (1);
	}
	if (!is_valid_file(argv[1]))
	{
		print_error("Bad extension");
		return (1);
	}
	init_game_values(&game);
	if (!parse_map(&game, argv[1]))
		return (1);
	if (!validate_map(&game))
		return (1);
	if (!check_map_path(&game))
		return (1);
	if (!init_game(&game))
		return (1);
	start_game(&game);
	return (0);
}
