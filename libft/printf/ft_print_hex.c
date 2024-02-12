/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:12:43 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/24 12:05:22 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_dec_to_hex(unsigned long num, char mode);

int	ft_print_ptr(va_list *args)
{
	unsigned long	ptr;
	char			*hex;
	int				len;

	ptr = (unsigned long) va_arg(*args, void *);
	len = ft_putstr("0x");
	if (len == -1)
		return (len);
	hex = ft_dec_to_hex(ptr, 0);
	if (!hex)
		return (-1);
	len = ft_putstr(hex);
	free(hex);
	if (len == -1)
		return (len);
	return (len + 2);
}

int	ft_print_x_low(va_list *args)
{
	unsigned int	x;
	char			*hex;
	int				len;

	x = va_arg(*args, unsigned int);
	hex = ft_dec_to_hex(x, 0);
	if (!hex)
		return (-1);
	len = ft_putstr(hex);
	free(hex);
	return (len);
}

int	ft_print_x_cap(va_list *args)
{
	unsigned int	x;
	char			*hex;
	int				len;

	x = va_arg(*args, unsigned int);
	hex = ft_dec_to_hex(x, 1);
	if (!hex)
		return (-1);
	len = ft_putstr(hex);
	free(hex);
	return (len);
}

static char	*ft_dec_to_hex(unsigned long num, char mode)
{
	char	*base;

	base = "0123456789abcdef\0""0123456789ABCDEF";
	base = base + (17 * mode);
	return (ft_dec_tobase(num, base));
}
