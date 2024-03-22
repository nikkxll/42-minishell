/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:16:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/22 17:44:21 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	wildcards(char ***arr)
{
	t_w_cards	wc;
	int			status;

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
	if (sort_and_fill_final_array(&wc) == MALLOC_ERR)
		return (MALLOC_ERR);
	*arr = wc.final_new_arr;
	return (SUCCESS);
}
