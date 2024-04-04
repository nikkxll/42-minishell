/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slashes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 01:23:36 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 01:23:52 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	remove_slashes(char **s)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	str = *s;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == SLASH && str[i + 1] == SLASH)
		{
			j = i;
			while (j < len)
			{
				str[j] = str[j + 1];
				j++;
			}
			len--;
			continue ;
		}
		i++;
	}
}
