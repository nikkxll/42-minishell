/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:31:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/25 22:33:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	A function that prints an error if export pattern was not followed
* @param	arr array of arguments or options if allowed
* @param	operations auxiliary array to calculate the number of operations
* of different type
* @return	`void`
*/
void	execute_error(char **arr, int *operations)
{
	int		j;

	j = -1;
	while (operations[++j])
	{
		if (operations[j] == EXPORT_ERROR)
			print_error_with_arg("not a valid identifier\n", arr[j],
				"export: ");
	}
}
