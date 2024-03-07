/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:35:29 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/07 19:50:32 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

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
