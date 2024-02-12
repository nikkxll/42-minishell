/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:06:12 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:51:02 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (*(s + i) != 0)
	{
		if (*(s + i) == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char) c == 0)
		return ((char *)s + i);
	return (0);
}
