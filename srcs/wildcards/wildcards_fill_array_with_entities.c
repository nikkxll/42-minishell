/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_fill_array_with_entities.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:39:27 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/15 11:07:41 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function to close the directory if allocation failed
 * @param	wc Pointer to wildcard expansion data
 * @return	@c `MALLOC_ERR`
 */
static int	auxiliary_closedir(t_w_cards *wc)
{
	closedir(wc->dir);
	return (MALLOC_ERR);
}

/**
 * @brief	Dot path ("./") in the string block
 * @param	wc Pointer to wildcard expansion data
 * @param	temp_arr_local Temporary array
 * @param	str The wildcard pattern string
 * @param	i pointer to the index of current pattern string
 * @return	@c `SUCCESS` if the array is successfully filled,
 * @c `MALLOC_ERR` if memory allocation fails
 */
static int	dot_path_constant_wildcards_block(t_w_cards *wc,
	char **temp_arr_local, char *str, int *i)
{
	char	*first;

	if (wildcard_strcmp(wc->entry->d_name, str + 2))
	{
		first = "./";
		temp_arr_local[*i] = ft_strjoin(first, wc->entry->d_name);
		if (!temp_arr_local[(*i)++])
			return (auxiliary_closedir(wc));
	}
	return (SUCCESS);
}

/**
 * @brief	Absolute path (from the root) in the string block
 * @param	wc Pointer to wildcard expansion data
 * @param	temp_arr_local Temporary array
 * @param	str The wildcard pattern string
 * @param	i pointer to the index of current pattern string
 * @return	@c `SUCCESS` if the array is successfully filled,
 * @c `MALLOC_ERR` if memory allocation fails
 */
static int	abs_path_constant_wildcards_block(t_w_cards *wc,
	char **temp_arr_local, char *str, int *i)
{
	char	*first;
	char	*second;

	if (wildcard_strcmp(wc->entry->d_name, ft_strrchr(str, SLASH) + 1))
	{
		first = getcwd(NULL, 0);
		if (!first)
			return (auxiliary_closedir(wc));
		second = ft_strjoin(first, "/");
		free(first);
		if (!second)
			return (auxiliary_closedir(wc));
		temp_arr_local[*i] = ft_strjoin(second, wc->entry->d_name);
		free(second);
		if (!temp_arr_local[(*i)++])
			return (auxiliary_closedir(wc));
	}
	return (SUCCESS);
}

/**
 * @brief	No path in the string block
 * @param	wc Pointer to wildcard expansion data
 * @param	temp_arr_local Temporary array
 * @param	str The wildcard pattern string
 * @param	i pointer to the index of current pattern string
 * @return	@c `SUCCESS` if the array is successfully filled,
 * @c `MALLOC_ERR` if memory allocation fails
 */
static int	no_path_wildcards_block(t_w_cards *wc, char **temp_arr_local,
	char *str, int *i)
{
	if (wildcard_strcmp(wc->entry->d_name, str))
	{
		temp_arr_local[*i] = ft_strdup(wc->entry->d_name);
		if (!temp_arr_local[(*i)++])
		{
			closedir(wc->dir);
			return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}

/**
 * @brief	Function contains condition block that processing different
 * categories of wildcard patterns
 * @param	wc Pointer to wildcard expansion data
 * @param	temp_arr_local Temporary array
 * @param	str The wildcard pattern string
 * @param	i pointer to the index of current pattern string
 * @return	@c `SUCCESS` if the array is successfully filled,
 * @c `MALLOC_ERR` if memory allocation fails
 */
int	fill_temp_array_conditions_block(t_w_cards *wc,
	char **temp_arr_local, char *str, int *i)
{
	if (wc->abs_path_flag == DOT_PATH)
	{
		if (dot_path_constant_wildcards_block(wc, temp_arr_local, str, i)
			== MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else if (wc->abs_path_flag == ABS_PATH)
	{
		if (abs_path_constant_wildcards_block(wc, temp_arr_local, str, i)
			== MALLOC_ERR)
			return (MALLOC_ERR);
	}
	else
	{
		if (no_path_wildcards_block(wc, temp_arr_local, str, i)
			== MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}
