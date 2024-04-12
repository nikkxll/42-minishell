/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_nl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:25:46 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/11 11:32:36 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_remove_nl(char *str)
{
	int			len;

	len = ft_strlen(str);
	if (len == 0)
		return ;
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}
