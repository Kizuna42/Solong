/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishino <kishino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:15 by kishino           #+#    #+#             */
/*   Updated: 2025/05/21 18:42:02 by kishino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	has_empty_line(char *raw)
{
	int	i;

	if (raw[0] == '\n')
		return (1);
	i = 0;
	while (raw[i])
	{
		if (raw[i] == '\n' && raw[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	print_count(char *before, int count, char *after)
{
	ft_putstr_fd(before, 1);
	ft_putnbr_fd(count, 1);
	ft_putstr_fd(after, 1);
}

void	*ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (NULL);
}

int	ft_berchr(char *str, char *cmp)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (cmp[y] == '\0' && str[i] == '\0')
		return (1);
	while (str[i])
	{
		while (str[i + y] == cmp[y] && str[i + y] && cmp[y])
			y++;
		if (cmp[y] == '\0' && str[i + y] == '\0')
			return (1);
		else
			y = 0;
		i++;
	}
	return (0);
}
