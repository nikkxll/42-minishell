/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:54:40 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/22 22:38:47 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/*
* Function that divides str with type T_COMMAND_BR in two parts
*
* Input:
* - `str` - string that coming from readline function
* - `i` - index to iterate through the string
* - `quote_type` - initialization for the variable in
* check_if_inside_quotes()
* 
* Output:
* - modified string if success, `NULL` otherwise
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

/*
* Auxiliary function for modificate_str_command_without_br()
*
* Input:
* - `str` - string that coming from readline function
* - `r` - new string for redirects
* - `i` - first index for iteration
* - `j` - second index for iteration
*/
static void	modificate_str_utils(char *str, char *r, int *i, int *j)
{
	r[*j] = str[*i];
	str[*i] = SPACE;
	(*j)++;
	(*i)++;
}

/*
* Function that allocates string for redirects and modifies current one
*
* Input:
* - `str` - string that coming from readline function
* - `redir` - new string allocated to store redirects
* - `i` - first index for iteration
* - `j` - second index for iteration
* 
* Output:
* - `-1` if malloc error occurs, `1` if success
*/
int	modificate_str_command_without_br(char *str, char **redir, int i,
			int j)
{
	char	*r;

	r = (char *)ft_calloc((int)ft_strlen(str), sizeof(char));
	if (!r)
		return (-1);
	while (str[i++] != NULL_TERM)
	{
		while (str[i] != REDIR_L && str[i] != REDIR_R && str[i] != NULL_TERM)
			i++;
		if (str[i] == REDIR_L || str[i] == REDIR_R)
		{
			while ((str[i] == REDIR_L || str[i] == REDIR_R
					|| str[i] == SPACE) && str[i] != NULL_TERM)
				modificate_str_utils(str, r, &i, &j);
			while (str[i] != SPACE && str[i] != NULL_TERM)
				modificate_str_utils(str, r, &i, &j);
		}
	}
	*redir = r;
	return (1);
}

/*
* Function that checks for brackets which are out of the quotes
*
* Input:
* - `str` - string that coming from readline function
* 
* Output:
* - `> 0` if exist, `0` otherwise
*/
int	brackets_search(char *str)
{
	int	i;
	int	quote_type;
	int	key;

	i = 0;
	quote_type = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}

/*
* Function that checks for redirects which are out of the quotes
*
* Input:
* - `str` - string that coming from readline function
* 
* Output:
* - `> 0` if exist, `0` otherwise
*/
int	redir_search(char *str)
{
	int	i;
	int	quote_type;
	int	key;

	i = 0;
	quote_type = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == REDIR_L || str[i] == REDIR_R)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}
