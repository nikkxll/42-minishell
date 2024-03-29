/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:32:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/26 17:05:32 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

/**
* @brief	A function that creates an array of quantities of various types of
* operations
* @param	arr array of arguments or options if allowed
* @param	envp an environment array
* @param	operations array to create
* @return	@c `MALLOC_ERR` if malloc failure occured, @c `SUCCESS` otherwise
*/
void	create_operations_array(char **arr, char **envp, int *operations)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (arr[++i] != NULL)
	{
		j = 0;
		while (ft_isenv(arr[i][j], &j))
			j++;
		if (arr[i][j] != EQUAL || j == 0)
			operations[i] = EXPORT_ERROR;
		else if (arr[i][j] == EQUAL && j > 0 && arr[i][j - 1] != UNSCORE)
		{
			if (env_var(envp, arr[i], -1, j) != -1
				|| arg_var(arr, arr[i], i, j) != -1)
				operations[i] = EXPORT_EDIT;
			else
				operations[i] = EXPORT_ADD;
		}
		else
			operations[i] = EXPORT_SKIP;
	}
}

/**
* @brief	A function that checks if any operation of @c `type` exist in an
* array @c `operations`
* @param	operations auxiliary array to calculate the number of operations
* of different type
* @param	i pointer to the index
* @param	j pointer to the index
* @param	type type to check
* @return	@c `1` if no operations with corresponding type, @c `0` otherwise
*/
int	check_operations(int *operations, int *i, int *j, int type)
{
	*i = 0;
	*j = -1;
	while (operations[++(*j)])
	{
		if (operations[*j] == type)
			(*i)++;
	}
	if (*i == 0)
		return (1);
	*j = -1;
	return (0);
}
