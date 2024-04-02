/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:39:50 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/27 15:49:33 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	return (dest);
}

char	*ft_free(char *s)
{
	free(s);
	return (0);
}

char	*add_to_string(char *s, char *buffer, size_t buf_len)
{
	size_t	s_len;
	size_t	new_len;
	char	*new_s;

	s_len = 0;
	while (s[s_len] != 0)
		s_len++;
	if ((size_t)(-1) - s_len - 1 < buf_len)
		return (ft_free(s));
	new_len = s_len + buf_len;
	new_s = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_s)
		return (ft_free(s));
	new_s[new_len] = 0;
	ft_strncpy(new_s, s, s_len);
	ft_strncpy(new_s + s_len, buffer, buf_len);
	free(s);
	return (new_s);
}

char	*check_string(char *s, int *status)
{
	if (!s)
	{
		s = (char *)malloc(sizeof(char) * 1);
		if (!s)
		{
			*status = 1;
			return (NULL);
		}
		*s = '\0';
	}
	return (s);
}
