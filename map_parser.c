/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:09:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/12 18:47:26 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static char	**read_map(char *filename, int height)
{
	int		fd;
	int		i;
	char	*line;
	char	**map;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

static int	check_map_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
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
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_map_borders(t_game *game)
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

static int	check_map_rectangular(t_game *game)
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

int	validate_map(t_game *game)
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
	if (!check_map_elements(game))
	{
		print_error("Map contains invalid characters.");
		free_map(&game->map);
		return (0);
	}
	if (game->map.player != 1 || game->map.exit != 1 || game->map.collectibles < 1)
	{
		print_error("Map must have 1 player, 1 exit, and at least 1 collectible.");
		free_map(&game->map);
		return (0);
	}
	return (1);
}

static int	flood_fill(char **map, int x, int y, int *collected)
{
	static int	exit_found = 0;

	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0' || map[y][x] == '1'
		|| map[y][x] == 'X')
		return (0);
	if (map[y][x] == 'C')
		(*collected)++;
	if (map[y][x] == 'E')
		exit_found = 1;
	map[y][x] = 'X';
	flood_fill(map, x + 1, y, collected);
	flood_fill(map, x - 1, y, collected);
	flood_fill(map, x, y + 1, collected);
	flood_fill(map, x, y - 1, collected);
	return (exit_found);
}

int	check_map_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		collected;
	int		exit_found;

	map_copy = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!map_copy)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		map_copy[i] = ft_strdup(game->map.grid[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (0);
		}
		i++;
	}
	map_copy[i] = NULL;
	collected = 0;
	exit_found = flood_fill(map_copy, game->map.player_pos.x,
						game->map.player_pos.y, &collected);
	i = 0;
	while (i < game->map.height)
		free(map_copy[i++]);
	free(map_copy);
	if (!exit_found || collected != game->map.collectibles)
	{
		print_error("No valid path found in map.");
		free_map(&game->map);
		return (0);
	}
	return (1);
}
