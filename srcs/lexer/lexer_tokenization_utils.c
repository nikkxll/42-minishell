/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenization_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:54:40 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/08 19:52:35 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Function that divides str with type @c `T_COMMAND_BR` in two parts
 * @param	str command line string
 * @param	i index to iterate through the string
 * @param	quote_type initialization for the variable in
 * @c `check_if_inside_quotes()`
 * @note	index @c `i` is changing using dereference operation
 * @return	modified string if success, @c `NULL` otherwise
 */
char	*command_part(char *str, int *i, int quote_type)
{
	while (str[*i] != NULL_TERM)
	{
		check_if_inside_quotes(str, i, &quote_type);
		if (!quote_type)
		{
			if (str[*i] == O_ROUND)
			{
				while (str[*i] != C_ROUND)
					(*i)++;
				if (str[*i] == C_ROUND)
				{
					str[(*i)++] = NULL_TERM;
					return (str);
				}
			}
			(*i)++;
		}
		else
			(*i)++;
	}
	return (NULL);
}

/**
 * @brief	Auxiliary function for @c `modificate_str_command_without_br()`
 * @param	str command line string
 * @param	r new string for redirects
 * @param	i pointer to the first index for iteration
 * @param	j pointer to the second index for iteration
 * @note	indexes @c `i` and @c `j` are changing using dereference
 * operation
 * @return	@c `void`
 */
static void	modificate_str_utils(char *str, char *r, int *i, int *j)
{
	r[*j] = str[*i];
	str[*i] = SPACE;
	(*j)++;
	(*i)++;
}

/**
 * @brief	Function that fills redir string with redirects info
 * @param	str command line string
 * @param	redir new string allocated to store redirects
 * @param	i pointer to the index for iteration
 * @param	j pointer to the index for iteration
 * @return	@c `void`
 */
static void	fill_redir(char *str, char **redir, int *i, int *j)
{
	int	q_flag;

	q_flag = 0;
	while ((str[*i] == REDIR_L || str[*i] == REDIR_R
			|| str[*i] == SPACE || str[*i] == HT) && str[*i] != NULL_TERM)
		modificate_str_utils(str, *redir, i, j);
	while (str[*i] != NULL_TERM)
	{
		if ((str[*i] == S_QUOTE || str[*i] == D_QUOTE) && q_flag == 0)
			q_flag = str[*i];
		else if (str[*i] == S_QUOTE && q_flag == S_QUOTE)
			q_flag = 0;
		else if (str[*i] == D_QUOTE && q_flag == D_QUOTE)
			q_flag = 0;
		if (q_flag == 0 && (str[*i] == SPACE || str[*i] == REDIR_L
				|| str[*i] == REDIR_R || str[*i] == HT || str[*i] == NULL_TERM))
			break ;
		else
			modificate_str_utils(str, *redir, i, j);
	}
	(*redir)[(*j)++] = SEPARATOR;
	(*i)--;
}

/**
 * @brief	Function that allocates string for redirects and modifies
 * current one
 * @param	str command line string
 * @param	redir new string allocated to store redirects
 * @param	i first index for iteration
 * @param	j second index for iteration
 * @return	@c `-1` if malloc error occurs, @c `1` if success
 */
int	modificate_str_command_without_br(char *str, char **redir, int i,
	int j)
{
	if (!str)
		return (-1);
	*redir = (char *)ft_calloc(ft_strlen(str) * 2, sizeof(char));
	if (!*redir)
		return (-1);
	while (str[i] != NULL_TERM)
	{
		while (str[i] != REDIR_L && str[i] != REDIR_R && str[i] != NULL_TERM)
			i++;
		if (str[i] == REDIR_L || str[i] == REDIR_R)
			fill_redir(str, redir, &i, &j);
		if (str[i] == NULL_TERM)
			break ;
		i++;
	}
	return (1);
}
