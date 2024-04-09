/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:00:01 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/08 12:40:10 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	A function that checks operation array for error types (0)
 * @param	arr array of arguments or options if allowed
 * @param	operations auxiliary array to calculate the number of operations
 * of different type
 * @return	@c `GENERIC_ERROR` which indicates if an error been found
 * @c `SUCCESS` if not
 */
int	check_for_errors(char **arr, int *operations)
{
	int	j;

	j = -1;
	while (arr[++j])
	{
		if (operations[j] == 0)
		{
			return (GENERIC_ERROR);
		}
	}
	return (SUCCESS);
}

/**
 * @brief	A function that prints an error if export pattern was not followed
 * @param	arr array of arguments or options if allowed
 * @param	operations auxiliary array to calculate the number of operations
 * of different type
 * @return	@c `flag` which indicates if any errors occured
 */
int	execute_other(char **arr, int *operations)
{
	int		j;
	int		i;

	j = -1;
	while (arr[++j])
	{
		if (operations[j] == EXPORT_ERROR)
		{
			i = 0;
			if (ft_isdigit(arr[j][i]))
				operations[j] = 0;
			while (ft_isenv(arr[j][i], &i))
				i++;
			if (arr[j][i] != NULL_TERM)
				operations[j] = 0;
		}
		if (operations[j] == 0)
		{
			print_arg_err_msg("export: `", arr[j],
				"': not a valid identifier\n");
		}
	}
	return (check_for_errors(arr, operations));
}
