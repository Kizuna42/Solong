/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:59 by kishino           #+#    #+#             */
/*   Updated: 2025/05/21 15:29:00 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * マップの列（縦）が壁で囲まれているかチェック
 *
 * @param map_line マップの行
 * @param wall 壁を表す文字
 * @param data ゲームデータ構造体
 * @return 有効なら1、無効なら0
 */
int	ft_check_col(char *map_line, char wall, t_data *data)
{
	int	i;

	i = 0;
	while (map_line[i])
		i++;
	if (map_line[0] != wall || map_line[i - 1] != wall)
	{
		ft_error("Error\nMap column not close\n");
		return (0);
	}
	data->width = i;
	return (1);
}

/**
 * マップの行（横）が壁のみで構成されているかチェック
 *
 * @param map_line マップの行
 * @param wall 壁を表す文字
 * @return 有効なら1、無効なら0
 */
int	ft_check_line(char *map_line, char wall)
{
	int	i;

	i = 0;
	while (map_line[i])
	{
		if (map_line[i] != wall)
		{
			ft_error("Error\nMap line not close\n");
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * マップが有効な記号のみで構成されているかチェック
 *
 * @param map_line マップの行
 * @param content ゲームコンテンツ構造体
 * @return 有効なら1、無効なら0
 */
int	ft_check_other(char *map_line, t_cnt *content)
{
	int	i;

	i = 0;
	while (map_line[i])
	{
		if (content->count_e > 1 || content->count_p > 1)
		{
			ft_error("Error\nWrong number of player or exit\n");
			return (0);
		}
		if (map_line[i] != content->wall && map_line[i] != content->player
			&& map_line[i] != content->exit && map_line[i] != content->collect
			&& map_line[i] != content->space)
		{
			ft_error("Error\nUnknown symbol(s) in map\n");
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * マップ内のオブジェクト数をカウント
 *
 * @param data ゲームデータ構造体
 */
void	ft_check_content(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (data->map[i])
	{
		while (data->map[i][y])
		{
			if (data->map[i][y] == data->content.collect)
				data->content.count_c += 1;
			if (data->map[i][y] == data->content.player)
				data->content.count_p += 1;
			if (data->map[i][y] == data->content.exit)
				data->content.count_e += 1;
			y++;
		}
		y = 0;
		i++;
	}
}

/**
 * マップが長方形または正方形かチェック
 *
 * @param map マップ配列
 * @return 有効なら1、無効なら0
 */
int	ft_check_format(char **map)
{
	int	y;
	int	x;
	int	count_x;

	x = 0;
	y = 0;
	count_x = 0;
	while (map[0][count_x])
		count_x++;
	while (map[y] != NULL)
	{
		while (map[y][x])
			x++;
		if (x != count_x)
		{
			ft_error("Error\nMap must be a rectangle or a square\n");
			return (0);
		}
		x = 0;
		y++;
	}
	return (1);
}
