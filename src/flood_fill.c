/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:51:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/05/24 20:25:47 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

static void	free_map_copy(char **map_copy, int height)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (i < height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static void	flood_fill_recursive(char **map, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	if (map[y][x] == data->content.wall || map[y][x] == 'F')
		return ;
	if (map[y][x] == data->content.collect)
		data->flood_collect_count++;
	if (map[y][x] == data->content.exit)
		data->flood_exit_found = 1;
	map[y][x] = 'F';
	flood_fill_recursive(map, x + 1, y, data);
	flood_fill_recursive(map, x - 1, y, data);
	flood_fill_recursive(map, x, y + 1, data);
	flood_fill_recursive(map, x, y - 1, data);
}

static int	find_player_position(char **map, t_data *data, int *x, int *y)
{
	int	i;
	int	j;

	*x = -1;
	*y = -1;
	i = 0;
	while (i < data->height && *x == -1)
	{
		j = 0;
		while (j < data->width && *x == -1)
		{
			if (map[i][j] == data->content.player)
			{
				*x = j;
				*y = i;
			}
			j++;
		}
		i++;
	}
	return (*x != -1);
}

int	check_map_solvable(t_data *data)
{
	char	**map_copy;
	int		player_x;
	int		player_y;

	map_copy = copy_map(data->map, data->height);
	if (!map_copy)
		return (0);
	if (!find_player_position(map_copy, data, &player_x, &player_y))
	{
		free_map_copy(map_copy, data->height);
		return (0);
	}
	data->flood_collect_count = 0;
	data->flood_exit_found = 0;
	flood_fill_recursive(map_copy, player_x, player_y, data);
	free_map_copy(map_copy, data->height);
	if (data->flood_collect_count != data->content.count_c
		|| data->flood_exit_found != 1)
		return (0);
	return (1);
}
