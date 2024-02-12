/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:11 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:50:41 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == 0 && src == 0)
		return (0);
	i = 0;
	if (dst > src)
	{
		while (i < len)
		{
			*((unsigned char *)dst + len - 1 - i)
				= *((unsigned char *)src + len - 1 - i);
			i++;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
