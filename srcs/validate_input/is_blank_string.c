/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:12:04 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/05 16:12:21 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_bool	is_blank_string(char *str)
{
	if (ft_strlen(str) == 0)
		return (true);
	while (*str == SPACE)
		str++;
	return (*str == NULL_TERM);
}
