/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:44:11 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:51:41 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	s_len -= start;
	substr = (char *)malloc(sizeof(char)
			* ((s_len) * (s_len < len) + (len) * (s_len >= len) + 1));
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, ((s_len) * (s_len < len) + (len)
			* (s_len >= len) + 1));
	return (substr);
}
