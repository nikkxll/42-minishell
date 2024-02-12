/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:02:34 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:51:12 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strcpy(char *dest, char *src);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	s1_len;
	size_t	s2_len;
	char	*s;

	if (!s1)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	len = s1_len + s2_len + 1;
	if (len <= s1_len || len <= s2_len)
		return (0);
	s = (char *)malloc(sizeof(char) * len);
	if (!s)
		return (0);
	s = ft_strcpy(s, (char *)s1);
	ft_strcpy(s + s1_len, (char *)s2);
	return (s);
}

static char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = 0;
	return (dest);
}
