/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:31:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/07 19:50:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
