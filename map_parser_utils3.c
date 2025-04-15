/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:26:45 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill(char **map, int x, int y, int *collected)
{
	int	exit_found;

	exit_found = 0;
	if (map[y][x] == 'E')
	{
		exit_found = 1;
		map[y][x] = 'X';
		return (exit_found);
	}
	if (map[y][x] == 'C')
		(*collected)++;
	map[y][x] = 'X';
	if (x > 0 && map[y][x - 1] != '1' && map[y][x - 1] != 'X')
		exit_found |= flood_fill(map, x - 1, y, collected);
	if (map[y][x + 1] != '\0' && map[y][x + 1] != '1' && map[y][x + 1] != 'X')
		exit_found |= flood_fill(map, x + 1, y, collected);
	if (y > 0 && map[y - 1] != NULL
		&& map[y - 1][x] != '1' && map[y - 1][x] != 'X')
		exit_found |= flood_fill(map, x, y - 1, collected);
	if (map[y + 1] != NULL && map[y + 1][x] != '1' && map[y + 1][x] != 'X')
		exit_found |= flood_fill(map, x, y + 1, collected);
	return (exit_found);
}

int	flood_fill_recursive(char **map, int x, int y, int *collected)
{
	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0'
		|| map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	return (flood_fill(map, x, y, collected));
}

char	**create_map_copy(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		map_copy[i] = ft_strdup(game->map.grid[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
