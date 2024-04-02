/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:16:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/31 23:55:50 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function that expands wildcard patterns in an initial array,
 * searches for files or directories matching the expanded patterns,
 * combines the matching records into a common 2D array, and returns it
 * @param	arr Pointer to the initial array with wildcard patterns
 * @return	@c `SUCCESS` if the operation completes successfully,
 * @c `MALLOC_ERR` if memory allocation fails during processing,
 * @c `SYSTEM_ERROR` if an error occurs in functions from imported libraries
 */
int	wildcards(char ***arr)
{
	t_w_cards	wc;
	int			status;

	if (!if_asterisk_in_arr(*arr, 0, 0))
		return (SUCCESS);
	status = allocate_temp_array(arr, &wc);
	if (status == MALLOC_ERR)
		return (MALLOC_ERR);
	if (status == SYSTEM_ERROR)
		return (SYSTEM_ERROR);
	status = fill_temp_array(arr, &wc);
	if (status == SYSTEM_ERROR)
		return (SYSTEM_ERROR);
	if (status == MALLOC_ERR)
		return (MALLOC_ERR);
	status = allocate_and_fill_expanded_array(&wc);
	if (status == MALLOC_ERR)
		return (MALLOC_ERR);
	ft_free_2d_array(*arr);
	ft_free_3d_array(wc.temp_arr, 1);
	*arr = wc.new_arr;
	return (SUCCESS);
}
