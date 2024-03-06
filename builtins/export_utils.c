/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:32:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/06 19:33:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	create_operations_array(char **arr, char **envp, int *operations)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (arr[++i] != NULL)
	{
		j = 0;
		while (arr[i][j] != EQUAL_SIGN && arr[i][j] != NULL_TERM
				&& arr[i][j] != SPACE && !ft_isdigit(arr[i][j]))
			j++;
		if ((arr[i][j] == SPACE) || (ft_isdigit(arr[i][j]) && j == 0))
			operations[i] = EXPORT_ERROR;
		else if (arr[i][j] == EQUAL_SIGN && j > 0 && arr[i][j - 1] != UNSCORE)
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
	return (0);
}
