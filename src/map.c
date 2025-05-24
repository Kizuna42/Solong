/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishino <kishino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:53 by kishino           #+#    #+#             */
/*   Updated: 2025/05/21 20:18:51 by kishino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*get_map(int fd)
{
	char	*line_map;
	char	*buff;
	int		char_count;
	char	*tmp_buff;

	line_map = ft_strdup("");
	buff = ft_strdup("");
	char_count = gnl(fd, &line_map);
	while (char_count > 0)
	{
		tmp_buff = buff;
		buff = ft_strjoin(buff, line_map);
		free(tmp_buff);
		free(line_map);
		line_map = ft_strdup("");
		char_count = gnl(fd, &line_map);
	}
	free(line_map);
	if (char_count < 0 || !*buff)
		return (free(buff), ft_error("Error\nWrong lecture map\n"));
	return (buff);
}

void	*ft_free_map(t_data *data)
{
	int	i;

	if (!data || !data->map)
		return (NULL);
	i = 0;
	while (data->map[i] != NULL)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
	return (NULL);
}

int	validate_map_structure(t_data *data)
{
	int	i;

	i = 1;
	if (!ft_check_format(data->map))
		return (0);
	if (!ft_check_line(data->map[0], data->content.wall))
		return (0);
	while (data->map[i])
	{
		if (!ft_check_col(data->map[i], data->content.wall, data)
			|| !ft_check_other(data->map[i], &(data->content)))
			return (0);
		i++;
	}
	data->height = i;
	return (ft_check_line(data->map[i - 1], data->content.wall));
}

char	**load_map(int fd, t_data *data)
{
	char	*raw_map;

	raw_map = get_map(fd);
	if (!raw_map)
		return (ft_free_map(data));
	data->map = ft_split(raw_map, '\n');
	free(raw_map);
	if (!data->map || !validate_map_structure(data))
		return (ft_free_map(data));
	ft_check_content(data);
	return (data->map);
}

char	**map_core(char **str, t_data *data)
{
	int	fd;

	fd = 0;
	data->map = NULL;
	if (ft_berchr(str[1], ".ber") == 0)
		return (ft_error("Error\nNo correct format map founded\n"));
	fd = open(str[1], O_RDONLY);
	if (fd <= 0)
		return (ft_error("Error\nFailed to open file\n"));
	if (!load_map(fd, data))
		return (NULL);
	if ((data->content.count_c == 0 || data->content.count_e != 1
			|| data->content.count_p != 1) && data->map != NULL)
	{
		ft_free_map(data);
		return (ft_error(
				"Error\nNeed 1 Player/Exit and at least 1 Object\n"));
	}
	return (data->map);
}
