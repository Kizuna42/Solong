/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 00:00:00 by kizuna            #+#    #+#             */
/*   Updated: 2026/11/12 00:00:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	destroy_img(void *mlx_ptr, void *img)
{
	if (mlx_ptr && img)
		mlx_destroy_image(mlx_ptr, img);
}

static void	destroy_images(t_data *data)
{
	destroy_img(data->mlx_ptr, data->img.img_wall);
	destroy_img(data->mlx_ptr, data->img.img_floor);
	destroy_img(data->mlx_ptr, data->img.img_collect);
	destroy_img(data->mlx_ptr, data->img.img_player);
	destroy_img(data->mlx_ptr, data->img.img_exit);
}

void	cleanup_exit(t_data *data, int status)
{
	ft_free_map(data);
	if (data->mlx_ptr)
	{
		destroy_images(data);
		if (data->mlx_win)
			mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(status);
}
