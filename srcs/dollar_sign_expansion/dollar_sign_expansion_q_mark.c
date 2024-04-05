/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion_q_mark.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:27:25 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/05 17:07:01 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function that runs while loop to search for dollar signs with 
 * question marks
 * @param	str string to search in
 * @param	last_ind pointer to the last part of the new string
 * @return	enviroment list position of expanding string if exist,
 * @c `NOTHING_TO_EXPAND` otherwise
 */
static int	expansion_qm(char *str, int *last_ind)
{
	int	i;
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[i] != NULL_TERM)
	{
		if ((double_q == 0 || double_q == 1)
			&& single_q != 1 && str[i] == D_SIGN
			&& str[i + 1] == Q_MARK)
		{
			str[i] = NULL_TERM;
			str[i + 1] = NULL_TERM;
			*last_ind = *last_ind + i + 2;
			return (i);
		}
		index_quotes(str, i, &single_q, &double_q);
		i++;
	}
	return (NOTHING_TO_EXPAND);
}

/**
 * @brief	Function that combines the new string by concatenating expanded part
 * with initial string
 * @param	ds_q pointer to structure which consist of used variables in the
 * @c `expand_dollar_sign_q_mark()`
 * @param	str string to search in
 * @return	enviroment list position of expanding string if exist,
 * @c `NOTHING_TO_EXPAND` otherwise
 */
static int	combine_new_str(t_ds *ds_q, char **str)
{
	ds_q->new_str = ft_calloc(ds_q->new_str_len, sizeof(char));
	if (!ds_q->new_str)
	{
		free(ds_q->middle);
		return (MALLOC_ERR);
	}
	ft_strlcat(ds_q->new_str, ds_q->first, ds_q->new_str_len);
	ft_strlcat(ds_q->new_str, ds_q->middle, ds_q->new_str_len);
	ft_strlcat(ds_q->new_str, ds_q->last, ds_q->new_str_len);
	free(ds_q->middle);
	free(*str);
	*str = ds_q->new_str;
	ds_q->last_ind = 0;
	return (SUCCESS);
}

/**
 * @brief	Function to expand last exit status indicated by '$?'
 * in a string
 * @note	This function iterates through the string and expands
 * last exit status indicated by '$?'
 * It replaces each '$?' with the corresponding number
 * @param	str Pointer to the string to be expanded
 * @param	last_exit_status last exit status to expand
 * @return	@c `SUCCESS` if the expansion is successful,
 * @c `MALLOC_ERR` if memory allocation fails during expansion
 */
int	expand_dollar_sign_q_mark(char **str, int last_exit_status)
{
	t_ds	ds_q;

	ds_q.last_ind = 0;
	ds_q.new_str = *str;
	while (expansion_qm(ds_q.new_str, &(ds_q.last_ind)) != NOTHING_TO_EXPAND)
	{
		ds_q.first = ds_q.new_str;
		ds_q.last = ds_q.new_str + ds_q.last_ind;
		ds_q.middle = ft_itoa(last_exit_status);
		if (!ds_q.middle)
			return (MALLOC_ERR);
		ds_q.new_str_len = ft_strlen(ds_q.first) + ft_strlen(ds_q.middle)
			+ ft_strlen(ds_q.last) + 1;
		if (combine_new_str(&ds_q, str) == MALLOC_ERR)
			return (MALLOC_ERR);
	}
	return (SUCCESS);
}
