/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion_generic.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:30:11 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/05 17:08:05 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Auxiliary function for @c `expansion()` function
 * @param	str string to search in
 * @param	envp environment array
 * @param	dollar pointer to structure which consist of used variables
 * @return	@c `void`
 */
static void	process_dollar_sign_in_string(char *str, char **envp,
	t_dollar_exp *dollar)
{
	dollar->k = dollar->i;
	while (ft_isenv(str[dollar->i], &(dollar->i)))
		(dollar->i)++;
	dollar->last_part_ind = dollar->i;
	dollar->env_list_pos = environment_search_exp_module(envp,
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

/**
 * @brief	Function that initialize @c `t_dollar` structure
 * @param	dollar pointer to structure which consist of used variables
 * @param	env_part pointer to the env string that has been found
 * @param	last_part_ind pointer to the last part of the new string
 * @return	@c `void`
 */
static void	dollar_struct_init(t_dollar_exp *dollar, char **env_part,
	int *last_part_ind)
{
	dollar->i = 0;
	dollar->k = 0;
	dollar->env_list_pos = 0;
	dollar->single_q = 0;
	dollar->double_q = 0;
	dollar->last_part_ind = *last_part_ind;
	dollar->env_part = *env_part;
}

/**
 * @brief	Function that runs while loop to search for dollar signs
 * @param	str string to search in
 * @param	envp environment array
 * @param	env_part pointer to the env string that has been found
 * @param	last_part_ind pointer to the last part of the new string
 * @return	enviroment list position of expanding string if exist,
 * @c `NOTHING_TO_EXPAND` otherwise
 */
static int	expansion(char *str, char **envp, char **env_part,
	int *last_part_ind)
{
	t_dollar_exp	dollar;

	dollar_struct_init(&dollar, env_part, last_part_ind);
	while (str[dollar.i] != NULL_TERM)
	{
		if ((dollar.double_q == 0 || dollar.double_q == 1)
			&& dollar.single_q != 1 && str[dollar.i] == D_SIGN)
		{
			if (++(dollar.i) && ft_isenv(str[dollar.i], &(dollar.i)))
			{
				process_dollar_sign_in_string(str, envp, &dollar);
				*env_part = dollar.env_part;
				*last_part_ind = dollar.last_part_ind;
				return (dollar.env_list_pos);
			}
			continue ;
		}
		index_quotes(str, dollar.i, &(dollar.single_q), &(dollar.double_q));
		(dollar.i)++;
	}
	return (NOTHING_TO_EXPAND);
}

/**
 * @brief	Function to expand environment variables indicated by '$'
 * in a string
 * @note	This function iterates through the string and expands
 * environment variables indicated by '$'
 * It replaces each '$' followed by a variable name with the corresponding
 * value from the environment
 * @param	str Pointer to the string to be expanded
 * @param	envp Environment variables array
 * @return	@c `SUCCESS` if the expansion is successful,
 * @c `MALLOC_ERR` if memory allocation fails during expansion
 */
int	expand_dollar_sign_generic(char **str, char **envp)
{
	t_ds	ds_q;

	ds_q.new_str = *str;
	ds_q.middle = NULL;
	while (expansion(ds_q.new_str, envp, &(ds_q.middle), &(ds_q.last_ind))
		!= NOTHING_TO_EXPAND)
	{
		ds_q.first = ds_q.new_str;
		ds_q.last = ds_q.new_str + ds_q.last_ind;
		ds_q.new_str_len = ft_strlen(ds_q.first) + ft_strlen(ds_q.middle)
			+ ft_strlen(ds_q.last) + 1;
		ds_q.new_str = ft_calloc(ds_q.new_str_len, sizeof(char));
		if (!ds_q.new_str)
			return (MALLOC_ERR);
		ft_strlcat(ds_q.new_str, ds_q.first, ds_q.new_str_len);
		ft_strlcat(ds_q.new_str, ds_q.middle, ds_q.new_str_len);
		ft_strlcat(ds_q.new_str, ds_q.last, ds_q.new_str_len);
		free(*str);
		*str = ds_q.new_str;
	}
	*str = ds_q.new_str;
	return (SUCCESS);
}
