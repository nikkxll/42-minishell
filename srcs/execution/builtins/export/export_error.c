/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:31:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/01 23:45:51 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

/**
 * @brief	A function that prints an error if export pattern was not followed
 * @param	arr array of arguments or options if allowed
 * @param	operations auxiliary array to calculate the number of operations
 * of different type
 * @return	@c `flag` which indicates if any errors occured
 */
int	execute_error(char **arr, int *operations)
{
	int		j;
	int		flag;

	j = -1;
	flag = 0;
	while (operations[++j])
	{
		if (operations[j] == EXPORT_ERROR)
		{
			print_arg_err_msg("export: `", arr[j],
				"': not a valid identifier\n");
			flag = 1;
		}
	}
	return (flag);
}
