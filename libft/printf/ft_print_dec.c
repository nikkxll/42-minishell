/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:12:43 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/09 12:30:13 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr(unsigned int n, char *str, int len);

int	ft_print_dec(va_list *args)
{
	int				num;
	char			sign;
	char			*str;
	int				len;

	num = va_arg(*args, int);
	if (num == -2147483648)
		return (ft_putstr("-2147483648"));
	sign = -1 * (num < 0) + 1 * (num >= 0);
	len = num < 0;
	len += ft_numlenbase(num * sign, 10);
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (-1);
	if (sign == -1)
	{
		*str = '-';
		ft_putnbr(num * sign, str + len - 1, len - 2);
	}
	else
		ft_putnbr(num, str + len - 1, len - 1);
	len = ft_putstr(str);
	free(str);
	return (len);
}

int	ft_print_unsigned_dec(va_list *args)
{
	unsigned int	num;
	char			*str;
	int				len;

	num = va_arg(*args, unsigned int);
	len = ft_numlenbase(num, 10);
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (-1);
	ft_putnbr(num, str + len - 1, len - 1);
	len = ft_putstr(str);
	free(str);
	return (len);
}

static void	ft_putnbr(unsigned int n, char *str, int len)
{
	if (len)
		ft_putnbr(n / 10, str - 1, len - 1);
	*str = n % 10 + 48;
}
