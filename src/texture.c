/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:23 by kishino           #+#    #+#             */
/*   Updated: 2025/05/24 17:33:23 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	chk_collect(t_data *data)
{
	int	i;
	int	y;
	int	count;

	i = 0;
	y = 0;
	count = 0;
	while (data->map[y])
	{
		while (data->map[y][i])
		{
			if (data->map[y][i] == data->content.collect)
				count++;
			i++;
		}
		i = 0;
		y++;
	}
	return (count);
}

int	end(t_data *data)
{
	cleanup_exit(data, 0);
	return (0);
}

int	key_press(int keysym, t_data *data)
{
	int	prev_count;

	prev_count = data->count;
	if (keysym == XK_Escape)
		end(data);
	if (keysym == XK_w)
		render_top(data);
	if (keysym == XK_d)
		render_right(data);
	if (keysym == XK_a)
		render_left(data);
	if (keysym == XK_s)
		render_down(data);
	if (data->count != prev_count)
		render(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_error("Error\nThis programe take 1 argument .ber\n");
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	set_content(&(data.content));
	if (map_core(argv, &data) == NULL)
		return (1);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		ft_free_map(&data);
		ft_error("Error\nFailed to initialize MiniLibX\n");
		return (1);
	}
	if (!set_img(&data))
		cleanup_exit(&data, 1);
	core_render(&data);
	return (0);
}
