/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_entities_expand.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:44:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/22 13:29:42 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	fill_temp_array_with_strings(char *str, char **temp_arr_local,
	t_w_cards *wc)
{
	int	i;

	i = 0;
	while (wc->entry != NULL && i < wc->ent_len)
	{
		if (wc->entry->d_name[0] == '.' && wc->dot_ind == false)
		{
			wc->entry = readdir(wc->dir);
			continue ;
		}
		if (wildcard_strcmp(wc->entry->d_name, str))
		{
			temp_arr_local[i] = ft_strdup(wc->entry->d_name);
			if (!temp_arr_local[i++])
			{
				closedir(wc->dir);
				return (MALLOC_ERR);
			}
		}
		wc->entry = readdir(wc->dir);
	}
	return (SUCCESS);
}

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

int	entities_expand(char ***temp_arr, char *str, t_w_cards *wc)
{
	char	**temp_arr_local;

	temp_arr_local = *temp_arr;
	wc->dot_ind = false;
	if (str[0] == '.')
		wc->dot_ind = true;
	wc->dir = opendir(".");
	if (wc->dir == NULL)
	{
		perror("Unable to open directory");
		return (SYSTEM_ERROR);
	}
	wc->entry = readdir(wc->dir);
	if (fill_temp_array_with_strings(str, temp_arr_local, wc) == MALLOC_ERR)
		return (MALLOC_ERR);
	if (closedir(wc->dir) == SYSTEM_ERROR)
	{
		perror("Unable to close directory");
		return (SYSTEM_ERROR);
	}
	if (empty_array_fill(temp_arr_local, str) == MALLOC_ERR)
		return (MALLOC_ERR);
	return (SUCCESS);
}
