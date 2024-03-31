/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_asterisk_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:45:58 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/31 23:55:17 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function that checks if there are any asterisks in an array
 * @param	arr array to check in
 * @param	i index
 * @param	j index
 * @param	quote_type initialization for quote check
 * @return	@c `true` if yes, @c `false` otherwise
 */
t_bool	if_asterisk_in_arr(char **arr, int i, int j)
{
	int	quote_type;

	quote_type = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j] != NULL_TERM)
		{
			check_if_inside_quotes(arr[i], &j, &quote_type);
			if (!quote_type)
			{
				if (arr[i][j++] == ASTERISK)
					return (true);
			}
			else
				j++;
		}
		i++;
	}
	return (false);
}
