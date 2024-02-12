/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:24:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/01/16 13:00:01 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putnbr(int nb, char *arr, int pos, int len);

static int	ft_num_len(int num);

char	*ft_itoa(int n)
{
	char	*arr;
	int		num_len;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	num_len = ft_num_len(n);
	arr = (char *)malloc(sizeof(char) * (num_len + 1));
	if (!arr)
		return (0);
	if (n < 0)
	{
		*arr = '-';
		ft_putnbr(n * -1, arr + 1, 0, num_len - 1);
	}
	else
		ft_putnbr(n, arr, 0, num_len);
	*(arr + num_len) = 0;
	return (arr);
}

static int	ft_num_len(int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = num < 0;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr(int nb, char *arr, int pos, int len)
{
	if (nb > 9)
		ft_putnbr(nb / 10, arr, pos + 1, len);
	*(arr + len - 1 - pos) = nb % 10 + 48;
}
