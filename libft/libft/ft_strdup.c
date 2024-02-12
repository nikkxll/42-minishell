/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:06:41 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:51:05 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strcpy(char *dest, char *src);

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*dest;

	len = ft_strlen(s1) + 1;
	dest = (char *)malloc(len * sizeof(char));
	if (!dest)
		return (0);
	ft_strcpy(dest, (char *)s1);
	return (dest);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = 0;
	return (dest);
}
