/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:22:45 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/09 10:11:43 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	size_t	printed_num;
	int		write_res;

	printed_num = 0;
	write_res = 0;
	while (*s)
	{
		write_res = ft_putchar(*s);
		if (write_res == -1)
			return (write_res);
		s++;
		printed_num += write_res;
	}
	return (printed_num);
}
