/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:11:23 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/29 18:48:13 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

//need to change later
int	run_exit(char **arr)
{
	if (!*arr)
		exit (1);
	exit(ft_atoi(arr[0]));
}
