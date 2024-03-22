/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_entities_expand.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:44:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/22 10:44:35 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	entities_expand(char ***temp_arr, char *str, t_w_cards *wc)
{
	int			i;
	char		**temp_arr_local;
	t_bool		dot_ind;

	i = 0;
	temp_arr_local = *temp_arr;
	dot_ind = false;
	if (str[0] == '.')
		dot_ind = true;
	wc->dir = opendir(".");
	if (wc->dir == NULL)
	{
		perror("Unable to open directory");
		return (SYSTEM_ERROR);
	}
	wc->entry = readdir(wc->dir);
	i = 0;
	while (wc->entry != NULL && i < wc->ent_len)
	{
		if (wc->entry->d_name[0] == '.' && dot_ind == false)
		{
			wc->entry = readdir(wc->dir);
			continue ;
		}
		if (wildcard_strcmp(wc->entry->d_name, str)
			&& ft_strncmp(wc->entry->d_name, ".", ft_strlen(wc->entry->d_name))
			&& ft_strncmp(wc->entry->d_name, "..", ft_strlen(wc->entry->d_name)))
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
	if (closedir(wc->dir) == SYSTEM_ERROR)
	{
		perror("Unable to close directory");
		return (SYSTEM_ERROR);
	}
	if (ft_arrlen((void **)temp_arr_local) == 0)
	{
		temp_arr_local[0] = ft_strdup(str);
		if (!temp_arr_local[0])
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}
