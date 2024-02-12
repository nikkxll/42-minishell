/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:06:12 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:51:35 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if ((unsigned char) c == 0)
		return ((char *)s + s_len);
	while (s_len > 0)
	{
		if (*(s + s_len) == (unsigned char) c)
			return ((char *)s + s_len);
		s_len--;
	}
	if (*s == (unsigned char) c)
		return ((char *)s);
	return (0);
}
