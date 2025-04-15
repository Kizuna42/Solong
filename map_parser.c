/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:17:33 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	parse_map(t_game *game, char *filename)
{
	int	height;

	height = count_map_height(filename);
	if (height <= 0)
	{
		print_error("Could not read map file.");
		return (0);
	}
	game->map.height = height;
	game->map.grid = read_map(filename, height);
	if (!game->map.grid)
	{
		print_error("Could not allocate memory for map.");
		return (0);
	}
	return (1);
}
