/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:16:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/21 23:48:30 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	entities_expand(char ***temp_arr, char *str, int ent_len)
{
	DIR			*dir;
	t_dirent	*entry;
	int			i;
	char		**temp_arr_local;
	t_bool		dot_ind;

	i = 0;
	temp_arr_local = *temp_arr;
	dot_ind = false;
	if (str[0] == '.')
		dot_ind = true;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Unable to open directory");
		return (SYSTEM_ERROR);
	}
	entry = readdir(dir);
	i = 0;
	while (entry != NULL && i < ent_len)
	{
		if (entry->d_name[0] == '.' && dot_ind == false)
		{
			entry = readdir(dir);
			continue ;
		}
		if (wildcard_strcmp(entry->d_name, str)
			&& ft_strncmp(entry->d_name, ".", ft_strlen(entry->d_name))
			&& ft_strncmp(entry->d_name, "..", ft_strlen(entry->d_name)))
		{
			temp_arr_local[i] = ft_strdup(entry->d_name);
			if (!temp_arr_local[i++])
			{
				closedir(dir);
				return (MALLOC_ERR);
			}
		}
		entry = readdir(dir);
	}
	if (closedir(dir) == SYSTEM_ERROR)
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

int	wildcards(char ***arr, int i, int j, int k)
{
	char	***temp_arr;
	char	**new_arr;
	int		arr_len;
	int		status;
	int		ent_len;

	arr_len = ft_arrlen((void **)(*arr));
	ent_len = array_with_entities_len(0);
	temp_arr = ft_calloc(arr_len + 1, sizeof(char **));
	if (!temp_arr)
		return (MALLOC_ERR);
	while (i < arr_len)
	{
		temp_arr[i] = ft_calloc(array_with_entities_len(0) + 1, sizeof(char *));
		if (!temp_arr[i++])
		{
			ft_free_3d_array(temp_arr, 0);
			return (MALLOC_ERR);
		}
	}
	i = -1;
	while (++i < arr_len)
	{
		status = entities_expand(&(temp_arr[i]), (*arr)[i], ent_len);
		if (status == MALLOC_ERR)
		{
			ft_free_3d_array(temp_arr, 0);
			return (MALLOC_ERR);
		}
		else if (status == SYSTEM_ERROR)
		{
			ft_free_3d_array(temp_arr, 0);
			return (SYSTEM_ERROR);
		}
	}
	i = -1;
	arr_len = 0;
	while (temp_arr[++i] != NULL)
		arr_len += ft_arrlen((void **)temp_arr[i]);
	new_arr = ft_calloc(arr_len + 1, sizeof(char *));
	if (!new_arr)
	{
		ft_free_3d_array(temp_arr, 0);
		return (MALLOC_ERR);
	}
	i = -1;
	while(temp_arr[++j])
	{
		k = -1;
		while (temp_arr[j][++k])
			new_arr[++i] = temp_arr[j][k];
	}
	i = -1;
	ft_free_2d_array(*arr);
	ft_free_3d_array(temp_arr, 1);
	*arr = new_arr;
	return (SUCCESS);
}
