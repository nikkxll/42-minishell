/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:23:19 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/23 11:59:57 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		len;
	int		cur_res;
	va_list	args;
	char	*s;

	va_start(args, str);
	len = 0;
	s = (char *)str;
	while (*s)
	{
		cur_res = ft_switch(&s, &args);
		if (cur_res == -1)
		{
			va_end(args);
			return (-1);
		}
		if (*s == '%')
			s++;
		len += cur_res;
		s++;
	}
	va_end(args);
	return (len);
}
