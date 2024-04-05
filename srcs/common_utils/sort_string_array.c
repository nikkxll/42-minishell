/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 20:06:54 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/03 20:07:10 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	A function that sorts subarray
 * @param	argv input array
 * @param	size array size
 * @return	@c `void`
 */
static void	sort_subarray(char *argv[], int size)
{
	int		j;
	int		k;
	char	*temp;

	j = 1;
	while (j < size)
	{
		if (ft_strcmp(*argv, argv[j]) > 0)
		{
			k = j;
			temp = argv[j];
			while (k != 0)
			{
				argv[k] = argv[k - 1];
				k--;
			}
			*argv = temp;
		}
		j++;
	}
}

/**
 * @brief	A function that sorts an array according to ASCII
 * @param	argv input array
 * @param	size array size
 * @return	sorted array
 */
char	**sort_string_arr(char **argv, int size)
{
	int		i;
	char	**res;

	res = (char **)ft_calloc(size + 1, sizeof(char *));
	if (res == NULL)
		return (NULL);
	ft_memcpy((void *)res, (void *)argv, sizeof(char *) * size);
	i = 0;
	while (i < size)
	{
		sort_subarray(res + i, size - i);
		i++;
	}
	return (res);
}
