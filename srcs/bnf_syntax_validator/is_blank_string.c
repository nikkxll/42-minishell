/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_blank_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:12:04 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:13 by dshatilo         ###   ########.fr       */
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
	while (ft_isspace(*str))
		str++;
	return (*str == NULL_TERM);
}
