/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_entities_expand.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:44:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/29 13:50:30 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function to fill the temporary array with strings matching the
 * wildcard pattern
 * @param	str The wildcard pattern string
 * @param	temp_arr_local Temporary array
 * @param	wc Pointer to wildcard expansion data
 * @return	@c `SUCCESS` if the array is successfully filled,
 * @c `MALLOC_ERR` if memory allocation fails
 */
int	fill_temp_array_with_strings(char *str, char **temp_arr_local,
	t_w_cards *wc)
{
	int		i;

	i = 0;
	while (wc->entry != NULL && i < wc->ent_len)
	{
		if (wc->entry->d_name[0] == '.' && wc->dot_ind == false)
		{
			wc->entry = readdir(wc->dir);
			continue ;
		}
		if (fill_temp_array_conditions_block(wc, temp_arr_local, str, &i)
			== MALLOC_ERR)
			return (MALLOC_ERR);
		wc->entry = readdir(wc->dir);
	}
	return (SUCCESS);
}

/**
 * @brief	Function to fill an empty array with a single string
 * @param	temp_arr_local Temporary array
 * @param	str The string to fill the array with
 * @return	@c `SUCCESS` if the array is successfully filled,
 * @c `MALLOC_ERR` if memory allocation fails
 */
static int	empty_array_fill(char **temp_arr_local, char *str)
{
	if (ft_arrlen((void **)temp_arr_local) == 0)
	{
		temp_arr_local[0] = ft_strdup(str);
		if (!temp_arr_local[0])
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}

/**
 * @brief	Function to expand wildcard entities and populate a temporary
 * array with matching strings
 * @param	temp_arr Pointer to the temporary array
 * @param	str The wildcard pattern string
 * @param	wc Pointer to wildcard expansion data
 * @param	local local array to dereference temporary array
 * @return	@c `SUCCESS` if expansion and population succeed,
 * @c `MALLOC_ERR` if memory allocation fails,
 * @c `SYSTEM_ERROR` if an error occurs in file operations
 */
int	entities_expand(char ***temp_arr, char *str, t_w_cards *wc, char **local)
{
	char	*slash_searcher;

	local = *temp_arr;
	slash_searcher = ft_strrchr(str, SLASH);
	wc->dot_ind = false;
	if ((slash_searcher != NULL && slash_searcher[1] == '.')
		|| (slash_searcher == NULL && str[0] == '.'))
		wc->dot_ind = true;
	wc->dir = opendir(".");
	if (wc->dir == NULL)
	{
		perror("Unable to open directory");
		return (SYSTEM_ERROR);
	}
	wc->entry = readdir(wc->dir);
	if (fill_temp_array_with_strings(str, local, wc) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (closedir(wc->dir) == SYSTEM_ERROR)
	{
		perror("Unable to close directory");
		return (SYSTEM_ERROR);
	}
	if (empty_array_fill(local, str) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (SUCCESS);
}
