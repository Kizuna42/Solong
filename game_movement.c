/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:59:36 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	can_move(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == '1')
		return (0);
	if (game->map.grid[new_y][new_x] == 'E'
		&& game->collected != game->map.collectibles)
		return (0);
	return (1);
}

static void	collect_item(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->collected++;
		game->map.grid[new_y][new_x] = '0';
	}
	if (game->map.grid[new_y][new_x] == 'E'
		&& game->collected == game->map.collectibles)
	{
		printf("Congratulations! You won!\n");
		close_game(game);
	}
}

void	move_player(t_game *game, int x, int y)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player_pos.x + x;
	new_y = game->map.player_pos.y + y;
	if (!can_move(game, new_x, new_y))
		return ;
	collect_item(game, new_x, new_y);
	game->map.grid[game->map.player_pos.y][game->map.player_pos.x] = '0';
	game->map.grid[new_y][new_x] = 'P';
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	game->moves++;
	printf("Moves: %d\n", game->moves);
}
