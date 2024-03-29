/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_before_wildcards.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:00:17 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/29 19:06:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
* @brief	Auxiliary function for the @c `array_build_before_wc()` that gets
* info from splits of initial arr
* @param	temp_3d_arr pointer to the temporary array of splits
* @param	arr pointer to the array of strings which are coming from dollar
* sign expansion block
* @param	new_arr_len pointer to the new array length
* @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
*/
static int	array_build_before_wc_split(char ****temp_3d_arr, char ***arr,
	int *new_arr_len)
{
	int		i;
	char	***temp_3d_arr_local;

	i = -1;
	temp_3d_arr_local = *temp_3d_arr;
	temp_3d_arr_local = ft_calloc(ft_arrlen((void **)*arr) + 1,
			sizeof(char **));
	if (!temp_3d_arr_local)
		return (MALLOC_ERR);
	while ((*arr)[++i])
	{
		temp_3d_arr_local[i] = wrapper_ft_split_with_quotes((*arr)[i]);
		if (!temp_3d_arr_local[i])
		{
			ft_free_3d_array(temp_3d_arr_local, 0);
			return (MALLOC_ERR);
		}
	}
	i = -1;
	*temp_3d_arr = temp_3d_arr_local;
	while ((temp_3d_arr_local)[++i] != NULL)
		*new_arr_len += ft_arrlen((void **)(temp_3d_arr_local)[i]);
	return (SUCCESS);
}

/**
* @brief	Function that splits strings in an array after dollar sign
* expansion block
* @param	arr array of strings which are coming from dollar sign
* expansion block
* @param	i index
* @param	j index
* @param	k index
* @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
*/
int	array_build_before_wc(char ***arr, int i, int k, int j)
{
	char	***temp_3d_arr;
	char	**new_built;
	int		new_arr_len;

	new_arr_len = 0;
	if (array_build_before_wc_split(&temp_3d_arr, arr, &new_arr_len)
		== MALLOC_ERR)
		return (MALLOC_ERR);
	new_built = ft_calloc(new_arr_len + 1, sizeof(char *));
	if (!new_built)
	{
		ft_free_3d_array(temp_3d_arr, 0);
		return (MALLOC_ERR);
	}
	i = -1;
	while ((temp_3d_arr)[++j])
	{
		k = -1;
		while ((temp_3d_arr)[j][++k])
			(new_built)[++i] = (temp_3d_arr)[j][k];
	}
	ft_free_3d_array(temp_3d_arr, 1);
	*arr = new_built;
	return (SUCCESS);
}
