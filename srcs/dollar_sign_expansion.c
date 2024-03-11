/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:30:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/11 20:24:34 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int	enviroment_search_exp_module(char **envp, char *var, int i, int j)
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

static void	index_quotes(char *str, int i, int *single_q, int *double_q)
{
	if (str[i] == S_QUOTE && !(*single_q) && !(*double_q))
		*single_q = 1;
	else if (str[i] == D_QUOTE && !(*double_q) && !(*single_q))
		*double_q = 1;
	else if (str[i] == S_QUOTE && !(*single_q) && *double_q == 1)
		*single_q = 2;
	else if (str[i] == D_QUOTE && !(*double_q) && *single_q == 1)
		*double_q = 2;
	else if (str[i] == S_QUOTE && *single_q)
		*single_q = 0;
	else if (str[i] == D_QUOTE && *double_q)
		*double_q = 0;
}

static void	process_dollar_sign_in_string(char *str, char **envp,
	t_dollar_exp *dollar)
{
	dollar->k = dollar->i;
	while (ft_isenv(str[dollar->i], &(dollar->i)))
		(dollar->i)++;
	dollar->last_part_ind = dollar->i;
	dollar->env_list_pos = enviroment_search_exp_module(envp,
		str + dollar->k, -1, dollar->i - dollar->k);
	if (dollar->env_list_pos != NOT_FOUND)
		dollar->env_part = envp[dollar->env_list_pos] + dollar->i
			- dollar->k + 1;
	else
		dollar->env_part = "\0";
	(dollar->k)--;
	str[(dollar->k)++] = NULL_TERM;
	while (ft_isenv(str[dollar->k], &(dollar->k)))
		str[(dollar->k)++] = NULL_TERM;
}

static int	expansion(char *str, char **envp, char **env_part,
	int *last_part_ind)
{
	t_dollar_exp	dollar;

	dollar.i = 0;
	dollar.k = 0;
	dollar.env_list_pos = 0;
	dollar.single_q = 0;
	dollar.double_q = 0;
	dollar.last_part_ind = *last_part_ind;
	dollar.env_part = *env_part;
	while (str[dollar.i] != NULL_TERM)
	{
		if ((dollar.double_q == 0 || dollar.double_q == 1)
			&& dollar.single_q != 1 && str[dollar.i] == D_SIGN
			&& ++(dollar.i) && ft_isenv(str[dollar.i], &(dollar.i)))
		{
			process_dollar_sign_in_string(str, envp, &dollar);
			*env_part = dollar.env_part;
			*last_part_ind = dollar.last_part_ind;
			return (dollar.env_list_pos);
		}
		index_quotes(str, dollar.i, &(dollar.single_q), &(dollar.double_q));
		(dollar.i)++;
	}
	return (NOTHING_TO_EXPAND);
}

int	expand_dollar_sign(char **str, char **envp, int last_ind)
{
	char	*new_str;
	char	*first_part;
	char	*env_part;
	char	*last_part;
	int		new_str_len;

	new_str = *str;
	env_part = NULL;
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
