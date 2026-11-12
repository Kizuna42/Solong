/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishino <kishino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:29 by kishino           #+#    #+#             */
/*   Updated: 2025/05/21 18:41:40 by kishino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	set_content(t_cnt *content)
{
	content->exit = 'E';
	content->player = 'P';
	content->wall = '1';
	content->space = '0';
	content->collect = 'C';
	content->count_p = 0;
	content->count_e = 0;
	content->count_c = 0;
}

static void	*load_xpm(t_data *data, char *path)
{
	return (mlx_xpm_file_to_image(data->mlx_ptr, path,
			&(data->img.width), &(data->img.height)));
}

int	set_img(t_data *data)
{
	data->img.height = 80;
	data->img.width = 80;
	data->img.floor = "./textures/floor_texture.xpm";
	data->img.wall = "./textures/wall_texture.xpm";
	data->img.collect = "./textures/collect.xpm";
	data->img.player = "./textures/mario_player.xpm";
	data->img.exit = "./textures/exit_texture.xpm";
	data->img.img_wall = load_xpm(data, data->img.wall);
	data->img.img_floor = load_xpm(data, data->img.floor);
	data->img.img_exit = load_xpm(data, data->img.exit);
	data->img.img_collect = load_xpm(data, data->img.collect);
	data->img.img_player = load_xpm(data, data->img.player);
	if (!data->img.img_wall || !data->img.img_floor || !data->img.img_exit
		|| !data->img.img_collect || !data->img.img_player)
	{
		ft_error("Error\nFailed to load textures\n");
		return (0);
	}
	return (1);
}
