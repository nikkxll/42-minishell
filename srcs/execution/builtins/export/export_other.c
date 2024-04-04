/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:00:01 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/04 18:37:27 by dnikifor         ###   ########.fr       */
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
	int		i;
	int		flag;

	j = -1;
	while (operations[++j])
	{
		flag = 0;
		if (operations[j] == EXPORT_ERROR)
		{
			i = 0;
			if (ft_isdigit(arr[j][i]))
				flag = 1;
			while (ft_isenv(arr[j][i], &i))
				i++;
			if (arr[j][i] != NULL_TERM)
				flag = 1;
		}
		if (flag == 1)
		{
			print_arg_err_msg("export: `", arr[j],
				"': not a valid identifier\n");
		}
	}
	return (flag);
}
