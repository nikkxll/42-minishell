/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:26:40 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/04 19:15:56 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	echo_write(char **arr, int flag, int i)
{
	if (!flag)
	{
		while (arr[i])
		{
			ft_putstr_fd(arr[i], 1);
			if (arr[i + 1])
				ft_putchar_fd(SPACE, 1);
			i++;
		}
		ft_putchar_fd(NL, 1);
	}
	else
	{
		while (arr[i])
		{
			ft_putstr_fd(arr[i], 1);
			if (arr[i + 1])
				ft_putchar_fd(SPACE, 1);
			i++;
		}
	}
	return (1);
}

int	run_echo(char **arr, int i, int j, int nl_flag)
{
	int	k;

	k = 0;
	while (arr[i])
	{
		k = i;
		j = 0;
		if (arr[i][j] == '-')
		{
			j++;
			while (arr[i][j] != NULL_TERM)
			{
				skip_characters(arr[i], &j, 110);
				if (arr[i][j] != NULL_TERM)
					return (echo_write(arr + k, nl_flag, 0));
			}
			i++;
			nl_flag = 1;
			continue ;
		}
		else
			return (echo_write(arr + k, nl_flag, 0));
	}
	return (1);
}
