/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:09:34 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/21 22:27:11 by dnikifor         ###   ########.fr       */
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
	char	*str;
	char	**env;
	int		i;

	i = 0;
	(void)ac;
	str = ft_strdup(av[1]);
	arr = wrapper_ft_split_with_quotes(str);
	env = cpy_env(envp);
	if (wildcards(&arr, 0, -1, -1) != 0)
	{
		printf("%s\n", "error occured");
		return (0);
	}
	while (arr[i])
	{
		if (expand_dollar_sign(&arr[i++], env, 0) == MALLOC_ERR)
			printf("%s\n", "malloc error");
	}
	processing(arr, 0);
	if (command_run(arr, &env) == MALLOC_ERR)
		printf("%s\n", "malloc error");
	ft_free_2d_array(arr);
	ft_free_2d_array(env);
	return (0);
}

// int main()
// {
//     char string[200] = "minishll";
//     char pattern[200] = "minishll";

//     if (wildcard_strcmp(string, pattern))
//         printf("Match\n");

//     else
//         printf("No Match\n");

//     return 0;
// }