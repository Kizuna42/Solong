/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 10:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2025/04/15 17:17:33 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("No exist map");
		return (0);
	}
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

static char	**init_map(int height, int fd)
{
	char	**map;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

static void	process_line(char *line, char **map, int i)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map[i] = line;
}

char	**read_map(char *filename, int height)
{
	int		fd;
	int		i;
	char	*line;
	char	**map;

	fd = open(filename, O_RDONLY);
	map = init_map(height, fd);
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, map, i++);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}
