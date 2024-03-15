/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:16:41 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/15 16:05:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <dirent.h>

typedef struct dirent	t_dirent;

// int	aftercheck(char *entity, char *new_str_pos)
// {
// 	int		len_diff;
// 	char	*cmp_str;

// 	cmp_str = ft_strdup(new_str_pos);
// 	if (!cmp_str)
// 		return (MALLOC_ERR);
// 	len_diff = ft_strlen(cmp_str) - ft_strlen(entity);
// 	cmp_str[len_diff] = NULL_TERM;
// 	while (!ft_strncmp(entity, cmp_str, ft_strlen(cmp_str)))
// 		entity += len_diff;
// 	free(cmp_str);
// 	return (ft_strlen(entity) == 0);
// }

// char	*ft_strrnstr(char *entity, char *str, int ent_len)
// {
// 	int		static_len;
// 	char	*new_str_pos;
// 	char	*current;

// 	static_len = ent_len;
// 	current = NULL;
// 	while (ent_len >= 0)
// 	{
// 		new_str_pos = ft_strnstr(entity + ent_len, str, static_len);
// 		if (new_str_pos)
// 			current = new_str_pos;
// 		ent_len--;
// 	}
// 	return (current);
// }

// // minishell
// // m*s**j*
// int	check_entity(char *entity, char *str, t_bool last_sym, char	*new_str_pos)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (str[i] != NULL_TERM && str[i] == ASTERISK)
// 		i++;
// 	if (str[i] != NULL_TERM)
// 	{
// 		j = i;
// 		while (str[j] != NULL_TERM && str[j] != ASTERISK)
// 			j++;
// 		str[j] = NULL_TERM;
// 		if (i == 0 && !ft_strncmp(entity, str, j))
// 			return (check_entity(new_str_pos + (j - i), str + j, last_sym, new_str_pos));
// 		else
// 		{
// 			new_str_pos = ft_strrnstr(entity, str + i, ft_strlen(entity));
// 			if (new_str_pos)
// 				return (check_entity(new_str_pos + (j - i), str + j, last_sym, new_str_pos));
// 			else
// 				return (0);
// 		}
// 	}
// 	else if (last_sym)
// 		return (1);
// 	else if (aftercheck(entity, new_str_pos) == MALLOC_ERR)
// 		return (MALLOC_ERR);
// 	else if (aftercheck(entity, new_str_pos))
// 		return (1);
// 	else
// 		return (0);
// 	return (1);
// }

// t_bool	is_last_asterisk(char *new_str)
// {
// 	return (new_str[ft_strlen(new_str) - 1] == ASTERISK);
// }

int	array_with_entities_len()
{
	DIR			*dir;
	t_dirent	*entry;
	int			sub_arr_len;

	sub_arr_len = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Unable to open directory");
		return (1);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		sub_arr_len++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (sub_arr_len);
}

int	entities_expand(char ***temp_arr, char *str)
{
	DIR			*dir;
	t_dirent	*entry;
	int			i;
	int			quote_type;
	char		**temp_arr_local;
	// int			last;

	i = 0;
	quote_type = 0;
	temp_arr_local = *temp_arr;
	// last = is_last_asterisk(str);
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Unable to open directory");
		return (1);
	}
	entry = readdir(dir);
	i = 0;
	while (entry != NULL)
	{
		if (wildcard_strcmp(entry->d_name, str))
		{
			temp_arr_local[i] = ft_strdup(entry->d_name);
			if (!temp_arr_local[i++])
				return (MALLOC_ERR);
		}
		entry = readdir(dir);
	}
	if (ft_arrlen((void **)temp_arr_local) == 0)
		temp_arr_local[0] = ft_strdup(str);
	closedir(dir);
	return (0);
}

int	wildcards(char ***arr)
{
	char	***temp_arr;
	char	**new_arr;
	int		wildcard_check;
	int		sub_arr_len;
	int		arr_len;
	int		i;

	i = 0;
	wildcard_check = 0;
	sub_arr_len = array_with_entities_len();
	arr_len = ft_arrlen((void **)(*arr));
	temp_arr = ft_calloc(arr_len + 1, sizeof(char **));
	if (!temp_arr)
		return (MALLOC_ERR);
	while (i < arr_len)
	{
		temp_arr[i] = ft_calloc(sub_arr_len + 1, sizeof(char *));
		if (!temp_arr[i++])
		{
			ft_free_3d_array(temp_arr, 0);
			return (MALLOC_ERR);
		}
	}
	i = -1;
	while (++i < arr_len)
		entities_expand(&(temp_arr[i]), (*arr)[i]);
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
	int j = -1;
	int k = -1;
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
