/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:40:56 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 11:09:56 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("INCORRECT NUMBER OF ARGUMENTS!\n");
		return (1);
	}
	ft_printf("Input is %s!\n", validate_input(argv[1]) == true ? "correct" : "incorrect");
	(void)argc;
	return (0);
}

// int	main(void)
// {
// 	ft_printf("Hello world!\n");
// 	return (0);
// }
