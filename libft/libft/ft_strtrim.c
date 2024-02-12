/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:44:02 by dshatilo          #+#    #+#             */
/*   Updated: 2023/11/28 11:51:38 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	if (!end)
		return (ft_strdup(""));
	while (*(s1 + start) != 0 && ft_strchr(set, *(s1 + start)))
		start++;
	while (end > 0 && ft_strchr(set, *(s1 + end)))
		end--;
	end++;
	if (end < start)
		end = start;
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
