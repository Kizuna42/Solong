/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:35:23 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.collectibles = 0;
	game->map.exit = 0;
	game->map.player = 0;
	game->map.player_pos.x = 0;
	game->map.player_pos.y = 0;
	game->moves = 0;
	game->collected = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./so_long [map.ber]");
		return (1);
	}
	if (!is_valid_file(argv[1]))
	{
		print_error("Error: Invalid file format. Use .ber files only.");
		return (1);
	}
	init_struct(&game);
	if (!parse_map(&game, argv[1]))
		return (1);
	if (!validate_map(&game))
		return (1);
	if (!check_map_path(&game))
		return (1);
	if (!init_game(&game))
		return (1);
	game_loop(&game);
	return (0);
}
