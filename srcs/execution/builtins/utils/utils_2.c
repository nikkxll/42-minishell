/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:35:29 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/26 17:05:39 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

/**
* @brief	A function that compare two strings (like original strcmp)
* @param	s1 first string
* @param	s2 second string
* @return	an integer greater than, equal to, or less than 0, according as
* the string s1 is greater than, equal to, or less than the string s2
*/
static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] != 0)
	{
		if ((unsigned char)s1[i] - (unsigned char)s2[i])
			return ((unsigned char) s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i] != 0)
		return (0 - (unsigned char)s2[i]);
	else
		return (0);
}

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

/**
* @brief	A function that allocates new array for the environment list
* @param	envp an environment array
* @return	new array
*/
char	**cpy_env(char **envp)
{
	char	**env;
	int		len;
	int		i;

	i = 0;
	len = ft_arrlen((void **)envp);
	env = ft_calloc(len + 1, sizeof(char *));
	if (!env)
		return (NULL);
	while (i < len)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			ft_free_2d_array((void *)env);
			return (NULL);
		}
		i++;
	}
	return (env);
}

/**
* @brief	A function that checks if characters allowed to be in the name
* of the env variable
* @param	c character
* @param	j pointer to the index
* @return	@c `true` if allowed, @c `false` otherwise
*/
t_bool	ft_isenv(char c, int *j)
{
	if (*j == 0 && ft_isdigit(c))
		return (false);
	return (ft_isalnum(c) || c == UNSCORE);
}
