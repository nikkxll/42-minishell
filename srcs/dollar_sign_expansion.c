/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:30:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/08 18:32:02 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	expand_var(char **envp, char **var, int position, int cut_len)
{
	int		new_len;
	char	*new_var;
	int		i;
	int		j;
	int		k;

	i = 0;
	new_len = ft_strlen(*var) - cut_len;
	new_var = ft_calloc(ft_strlen(envp[position]) + new_len, sizeof(char));
	if (!new_var)
		return (MALLOC_ERR);
	while (var[0][i])
	{
		if (var[0][i] == D_SIGN && ft_isenv(var[0][i + 1], &i))
		{
			j = 0;
			k = -1;
			while (envp[position][++k + cut_len])
				new_var[j++] = envp[position][k + cut_len];
			i += cut_len;
			continue ;
		}
		new_var[j] = var[0][i];
		j++;
		i++;
	}
	free(*var);
	*var = new_var;
	return (SUCCESS);
}

int	dollar_sign_expansion(char **arr, char **envp)
{
	int	i;
	int	j;
	int	k;
	int	position;

	i = -1;
	j = -1;
	k = 0;
	position = 0;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if (arr[i][j] == D_SIGN)
			{
				j++;
				k = j;
				while (ft_isenv(arr[i][j], &j))
					j++;
				position = env_var(envp, arr[i] + k, -1, j - k);
				if (position != -1)
				{
					if (expand_var(envp, &arr[i], position, j - k + 1)
						== MALLOC_ERR)
						return (MALLOC_ERR);
					else
						break ;
				}
			}
		}
	}
	return (SUCCESS);
}
