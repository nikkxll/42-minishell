/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/30 12:33:22 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

//need to change later
int	run_exit(char **arr)
{
	ft_putstr_fd("exit\n", 1);
	if (!*arr)
		exit (0);
	exit(ft_atoi(arr[0]));
}
