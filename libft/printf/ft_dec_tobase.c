/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_tobase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:04:51 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/09 12:25:15 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_dec_tobase(unsigned long num, char *base)
{
	char	*str;
	int		b_len;
	int		num_len;
	int		i;

	if (num == 0)
	{
		str = (char *)ft_calloc(sizeof(char), 2);
		if (!str)
			return (0);
		*str = *base;
		return (str);
	}
	num_len = ft_numlenbase(num, 16);
	b_len = ft_strlen(base);
	str = (char *)ft_calloc(sizeof(char), (num_len + 1));
	if (!str)
		return (0);
	i = 0;
	while (num != 0)
	{
		str[num_len - 1 - i++] = base[num % b_len];
		num = (num - num % b_len) / b_len;
	}
	return (str);
}
