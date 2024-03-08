/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:40:56 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/08 18:28:38 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// int	main(void)
// {
// 	ft_printf("Hello world!\n");
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	int		status;
	char	**arr;
	char	**env;
	int		i;

	av[2] = "$PATH$PATH";
	i = 0;
	arr = ft_calloc(ac, sizeof(char *));
	env = cpy_env(envp);
	while (i < ac - 1)
	{
		arr[i] = ft_calloc(ft_strlen(av[i + 1]) + 1, sizeof(char));
		ft_memcpy(arr[i], av[i + 1], ft_strlen(av[i + 1]));
		i++;
	}
	arr[i] = NULL;
	processing(arr, 0);
	dollar_sign_expansion(arr, env);
//
	// i = -1;
	// while (arr[++i])
	// 	printf("%s\n", arr[i]);
//
	status = command_run(arr, &env);
	if (status == MALLOC_ERR)
		printf("%s\n", "malloc error");
//
	// printf("\n\n\n\n\n");
	// int k = -1;
	// while (env[++k])
	// 	printf("%s\n", env[k]);
//
	ft_free_2d_array(arr);
	ft_free_2d_array(env);
	return (0);
}
