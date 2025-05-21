/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kizuna <kizuna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:06:15 by kishino           #+#    #+#             */
/*   Updated: 2025/05/21 15:26:47 by kizuna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * 文字列内のすべての文字が同じかチェックする
 *
 * @param str チェックする文字列
 * @return 全ての文字が同じなら1、そうでなければ0、NULLなら-1
 */
int	ft_same_char(char *str)
{
	int		i;
	char	buff;

	i = 0;
	buff = '1';
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] != buff && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * エラーメッセージを標準エラー出力に書き込む
 *
 * @param str 出力するエラーメッセージ
 * @return 常にNULL
 */
void	*ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (NULL);
}

/**
 * 文字列がベルチャーター（.ber）で終わるかチェックする
 *
 * @param str チェックする文字列
 * @param cmp 比較する拡張子文字列
 * @return 一致する場合は1、しない場合は0
 */
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
