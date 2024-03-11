/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:40:56 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/11 20:25:54 by dnikifor         ###   ########.fr       */
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
	char	**arr;
	char	**env;
	int		i;

	av[2] = "\"$PWD\"''";
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
	i = 0;
	
//execute	
	while (arr[i])	
	{
		if (expand_dollar_sign(&arr[i++], env, 0) == MALLOC_ERR)
			printf("%s\n", "malloc error");
	}
	processing(arr, 0);
	if (command_run(arr, &env) == MALLOC_ERR)
		printf("%s\n", "malloc error");
//

	// printf("\n\n\n\n\n");
	// int k = -1;
	// while (env[++k])
	// 	printf("%s\n", env[k]);

	ft_free_2d_array(arr);
	ft_free_2d_array(env);
	return (0);
}
