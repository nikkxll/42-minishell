/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_blank_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:12:04 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/26 19:03:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function to check if a string consists only of whitespace
 * characters
 * @param	str Pointer to the string to be checked
 * @return	@c `true` if the string is empty or contains only whitespace
 * characters, @c `false` otherwise
 */
t_bool	is_blank_string(char *str)
{
	if (ft_strlen(str) == 0)
		return (true);
	while (*str == SPACE)
		str++;
	return (*str == NULL_TERM);
}
