/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:41:21 by kishino           #+#    #+#             */
/*   Updated: 2025/05/24 20:25:58 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>

// get_next_line関数のプロトタイプ
char	*get_next_line(int fd);

typedef struct img_s
{
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_wall;
	void	*img_collect;
	int		height;
	int		width;
	char	*player;
	char	*floor;
	char	*wall;
	char	*collect;
	char	*exit;
}				t_img;

typedef struct cnt_s
{
	char	exit;
	char	collect;
	char	player;
	char	wall;
	char	space;
	int		count_p;
	int		count_e;
	int		count_c;
}				t_cnt;

typedef struct pos_s
{
	int		x;
	int		y;
}				t_pos;

typedef struct data_s
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		width;
	int		height;
	char	**map;
	t_cnt	content;
	t_img	img;
	t_pos	pos;
	int		count;
	int		flood_collect_count;
	int		flood_exit_found;
}				t_data;

int		ft_berchr(char *str, char *cmp);
void	*ft_error(char *str);
int		ft_same_char(char *str);
char	*get_map(int fd);
char	**map_core(char **str, t_data *data);
int		chk_map(char **argv);
int		ft_check_col(char *map_line, char col, t_data *data);
int		ft_check_line(char *map_line, char wall);
int		ft_check_other(char *map_line, t_cnt *content);
void	ft_check_content(t_data *data);
int		ft_check_format(char **map);
int		chk_collect(t_data *data);
void	set_img(t_data *data);
void	set_content(t_cnt *content);
void	core_render(t_data *data);
int		render(t_data *data);
void	render_other(t_data *data);
void	render_background(t_data *data);
void	render_down(t_data *data);
void	render_left(t_data *data);
void	render_right(t_data *data);
void	render_top(t_data *data);
void	print_img(t_data *data, void *img, int x, int y);
int		key_press(int keysym, t_data *data);
int		end(t_data *data);
int		check_map_solvable(t_data *data);

#endif
