/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:30:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/10 12:47:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	search_env_var_exp_module(char **envp, char *var, int i, int j)
{
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, j) == 0)
		{
			if (envp[i][j] == EQUAL)
				return (i);
		}
	}
	return (NOT_FOUND);
}

static void	replace_chars_with_null_terms(char *str, int *k)
{
	(*k)--;
	str[(*k)++] = NULL_TERM;
	while (ft_isenv(str[*k], k))
		str[(*k)++] = NULL_TERM;
}

static int	expansion(char *str, char **envp, char **env_part,
	int *last_part_ind)
{
	int	i;
	int	k;
	int	position;

	i = 0;
	k = 0;
	position = 0;
	while (str[i] != NULL_TERM)
	{
		if (str[i++] == D_SIGN && ft_isenv(str[i], &i))
		{
			k = i;
			while (ft_isenv(str[i], &i))
				i++;
			*last_part_ind = i;
			position = search_env_var_exp_module(envp, str + k, -1, i - k);
			if (position != NOT_FOUND)
				*env_part = envp[position] + i - k + 1;
			else
				*env_part = "\0";
			replace_chars_with_null_terms(str, &k);
			return (position);
		}
	}
	return (NOTHING_TO_EXPAND);
}

int	expand_dollar_sign(char **str, char **envp, int last_ind,
	int new_str_len)
{
	char	*new_str;
	char	*first_part;
	char	*env_part;
	char	*last_part;

	new_str = *str;
	env_part = NULL;
	last_ind = 0;
	while (expansion(new_str, envp, &env_part, &last_ind) != NOTHING_TO_EXPAND)
	{
		first_part = new_str;
		last_part = new_str + last_ind;
		new_str_len = ft_strlen(first_part) + ft_strlen(env_part)
			+ ft_strlen(last_part) + 1;
		new_str = ft_calloc(new_str_len, sizeof(char));
		if (!new_str)
			return (MALLOC_ERR);
		ft_strlcat(new_str, first_part, new_str_len);
		ft_strlcat(new_str, env_part, new_str_len);
		ft_strlcat(new_str, last_part, new_str_len);
		free(*str);
		*str = new_str;
	}
	*str = new_str;
	return (SUCCESS);
}
