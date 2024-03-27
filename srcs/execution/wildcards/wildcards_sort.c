/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:42:40 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/27 16:00:34 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Function that joins sorted final array with command string
 * @param	arr pointer to the initial array
 * @param	str command string
 * @return	joined array
 */
char	**str_array_join(char **arr, char *str)
{
	char	**joined_arr;
	int		len;
	int		i;

	i = -1;
	len = ft_arrlen((void **)arr);
	joined_arr = ft_calloc(len + 2, sizeof(char *));
	if (!joined_arr)
		return (NULL);
	joined_arr[0] = str;
	while (++i < len)
		joined_arr[i + 1] = arr[i];
	return (joined_arr);
}

/**
 * @brief	Function that sorts and then joins command to the top of the array
 * @param	wc pointer to the structure with local variables initiated in
 * @c `wildcards()`
 * @param	arr pointer to the array
 * @return	@c `SUCCESS` if no errors occured, @c `MALLOC_ERR` if one of the
 * mallocs failed
 */
int	sort_array_with_command_inside(t_w_cards *wc, char ***arr)
{
	wc->sorted_new_arr = sort_string_arr(*arr + 1,
			ft_arrlen((void **)(*arr)) - 1);
	if (!wc->sorted_new_arr)
	{
		ft_free_3d_array(wc->temp_arr, 0);
		return (MALLOC_ERR);
	}
	wc->final_new_arr = str_array_join(wc->sorted_new_arr, (*arr)[0]);
	if (!wc->final_new_arr)
	{
		ft_free_3d_array(wc->temp_arr, 0);
		ft_free_2d_array(wc->sorted_new_arr);
		return (MALLOC_ERR);
	}
	free(*arr);
	free(wc->sorted_new_arr);
	*arr = wc->final_new_arr;
	return (SUCCESS);
}

/**
 * @brief	Processes sorting for elements in an array based on if a
 * command inside the array
 * @param	wc Pointer to the wildcard structure
 * @param	i Pointer to the index of the current element being processed
 * @return	@c `SUCCESS` if sorting is successful, @c `MALLOC_ERR`
 * if memory allocation fails
 */
int	array_sorting_process(t_w_cards *wc, int *i)
{
	char	**sorted_arr;
	if (*i == 0)
	{
		if (sort_array_with_command_inside(wc, &((wc->temp_arr)[*i]))
				== MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
	{
		sorted_arr = sort_string_arr((wc->temp_arr)[*i],
				ft_arrlen((void **)((wc->temp_arr)[*i])));
		if (!(wc->temp_arr)[*i])
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (MALLOC_ERR);
		}
		free((wc->temp_arr)[*i]);
		(wc->temp_arr)[*i] = sorted_arr;
	}
	return (SUCCESS);
}
