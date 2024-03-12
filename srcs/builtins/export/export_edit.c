/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:28:14 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/08 13:22:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	edit_env_list_substitution(char **arr, char **result, int *i,
	int *j)
{
	int		position;
	char	*new_var;

	while (arr[*j][*i] != EQUAL)
		(*i)++;
	position = env_var(result, arr[*j], -1, *i);
	new_var = ft_strdup(arr[*j]);
	if (new_var == NULL)
	{
		ft_free_2d_array(result);
		return (MALLOC_ERR);
	}
	free(result[position]);
	result[position] = new_var;
	return (SUCCESS);
}

int	edit_env_list(char ***new_env, char **arr, int *operations)
{
	int		i;
	int		j;
	char	**result;

	result = *new_env;
	if (check_operations(operations, &i, &j, EXPORT_EDIT))
		return (SUCCESS);
	i = 0;
	while (operations[++j])
	{
		if (operations[j] == EXPORT_EDIT)
		{
			if (edit_env_list_substitution(arr, result, &i, &j) == MALLOC_ERR)
				return (MALLOC_ERR);
		}
	}
	return (SUCCESS);
}
