/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansion_q_mark.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:27:25 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/02 14:50:16 by dnikifor         ###   ########.fr       */
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
static int	expansion_q_mark(char *str, int *last_ind)
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
 * @brief	Function to expand last exit status indicated by '$?'
 * in a string
 * @note	This function iterates through the string and expands
 * last exit status indicated by '$?'
 * It replaces each '$?' with the corresponding number
 * @param	str Pointer to the string to be expanded
 * @param	last_ind The index of the last part of the string
 * @param	last_exit_status last exit status to expand
 * @return	@c `SUCCESS` if the expansion is successful,
 * @c `MALLOC_ERR` if memory allocation fails during expansion
 */
int	expand_dollar_sign_q_mark(char **str, int last_ind,
	int last_exit_status)
{
	char	*new_str;
	char	*first_part;
	char	*exit_part;
	char	*last_part;
	int		new_str_len;

	new_str = *str;
	while (expansion_q_mark(new_str, &last_ind) != NOTHING_TO_EXPAND)
	{
		first_part = new_str;
		last_part = new_str + last_ind;
		exit_part = ft_itoa(last_exit_status);
		new_str_len = ft_strlen(first_part) + ft_strlen(exit_part)
			+ ft_strlen(last_part) + 1;
		new_str = ft_calloc(new_str_len, sizeof(char));
		if (!new_str)
			return (MALLOC_ERR);
		ft_strlcat(new_str, first_part, new_str_len);
		ft_strlcat(new_str, exit_part, new_str_len);
		ft_strlcat(new_str, last_part, new_str_len);
		free(*str);
		*str = new_str;
		last_ind = 0;
	}
	return (SUCCESS);
}
