/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:45:50 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/26 20:02:49 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
int	sort_array_with_command(char ***arr);
/**
* @brief	Function that allocates @c `len(arr)` 2d arrays
* @param	arr pointer to the initial array
* @param	wc pointer to the structure with local variables initiated in
* @c `wildcards()`
* @return	@c `SUCCESS` if no errors occured, @c `MALLOC_ERR` if one of the
* mallocs failed, @c `SYSTEM_ERROR` if error occured in the functions from
* imported libraries
*/
int	allocate_temp_array(char ***arr, t_w_cards *wc)
{
	int	i;

	i = 0;
	wc->arr_len = ft_arrlen((void **)(*arr));
	wc->ent_len = array_with_entities_len(0);
	if (wc->ent_len == SYSTEM_ERROR)
		return (SYSTEM_ERROR);
	wc->temp_arr = ft_calloc(wc->arr_len + 1, sizeof(char **));
	if (!wc->temp_arr)
		return (MALLOC_ERR);
	while (i < wc->arr_len)
	{
		(wc->temp_arr)[i] = ft_calloc(array_with_entities_len(0) + 1,
				sizeof(char *));
		if (!(wc->temp_arr)[i++])
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}

/**
* @brief	Function that fills @c `len(arr)` 2d arrays
* @param	arr pointer to the initial array
* @param	wc pointer to the structure with local variables initiated in
* @c `wildcards()`
* @return	@c `SUCCESS` if no errors occured, @c `MALLOC_ERR` if one of the
* mallocs failed, @c `SYSTEM_ERROR` if error occured in the functions from
* imported libraries
*/
int	fill_temp_array(char ***arr, t_w_cards *wc)
{
	int	i;

	i = -1;
	while (++i < wc->arr_len)
	{
		wc->status = entities_expand(&((wc->temp_arr)[i]), (*arr)[i], wc);
		if (wc->status == MALLOC_ERR)
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (MALLOC_ERR);
		}
		else if (wc->status == SYSTEM_ERROR)
		{
			ft_free_3d_array(wc->temp_arr, 0);
			return (SYSTEM_ERROR);
		}
	}
	return (SUCCESS);
}

/**
 * @brief	Function that create and fill extended 2d array
 * @param	wc pointer to the structure with local variables initiated in
 * @c `wildcards()`
 * @return	@c `SUCCESS` if no errors occured, @c `MALLOC_ERR` if one of the
 * mallocs failed
 */
int	allocate_and_fill_expanded_array(t_w_cards *wc)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	wc->arr_len = 0;
	while ((wc->temp_arr)[++i] != NULL)
		wc->arr_len += ft_arrlen((void **)(wc->temp_arr)[i]);
	wc->new_arr = ft_calloc(wc->arr_len + 1, sizeof(char *));
	if (!wc->new_arr)
	{
		ft_free_3d_array(wc->temp_arr, 0);
		return (MALLOC_ERR);
	}
	i = -1;
	while ((wc->temp_arr)[++j])
	{
		k = -1;
		while ((wc->temp_arr)[j][++k])
			(wc->new_arr)[++i] = (wc->temp_arr)[j][k];
	}
	return (SUCCESS);
}

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
 * @brief	Function that sorts and then joins final array
 * @param	wc pointer to the structure with local variables initiated in
 * @c `wildcards()`
 * @return	@c `SUCCESS` if no errors occured, @c `MALLOC_ERR` if one of the
 * mallocs failed
 */
int	sort_and_fill_final_array(t_w_cards *wc)
{
	wc->sorted_new_arr = sort_string_arr(wc->new_arr + 1,
			ft_arrlen((void **)wc->new_arr) - 1);
	if (!wc->sorted_new_arr)
	{
		ft_free_2d_array(wc->new_arr);
		return (MALLOC_ERR);
	}
	wc->final_new_arr = str_array_join(wc->sorted_new_arr, (wc->new_arr)[0]);
	free(wc->new_arr);
	free(wc->sorted_new_arr);
	return (SUCCESS);
}
