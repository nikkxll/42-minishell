/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:54 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/25 22:48:27 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	Removes quotes from the string if allowable
* @param	str string that coming from readline function
* @param	i index
* @param	j index
* @return	`void`
*/
void	remove_quotes(char *str, int i, int j)
{
	int	len;
	int	inside_quotes;

	len = ft_strlen(str);
	inside_quotes = 0;
	while (i < len)
	{
		if ((str[i] == S_QUOTE || str[i] == D_QUOTE) && !inside_quotes)
			inside_quotes = str[i];
		else if (str[i] == S_QUOTE && inside_quotes == S_QUOTE)
			inside_quotes = 0;
		else if (str[i] == D_QUOTE && inside_quotes == D_QUOTE)
			inside_quotes = 0;
		else if (str[i] == SPACE && !inside_quotes)
			break ;
		else
			str[j++] = str[i];
		i++;
	}
	while (i < len)
		str[j++] = str[i++];
	str[j] = NULL_TERM;
}

/**
* @brief	Skips all `symbol` characters in a string
* @param	str string to skip chars in
* @param	i pointer to the index
* @param	symbol character
* @return	`void`
*/
void	skip_characters(char *str, int *i, int symbol)
{
	while (str[*i] == symbol && str[*i] != NULL_TERM)
		(*i)++;
}

/**
* @brief	A function that runs `remove_quotes()` function in a loop
* @param	arr array of arguments
* @param	i an index
* @return	`void`
*/
void	processing(char **arr, int i)
{
	while (arr[i])
		remove_quotes(arr[i++], 0, 0);
}

/**
* @brief	A function that checks if `var` included in the enviroment
* list
* @param	envp an enviroment array
* @param	var search string
* @param	i an index
* @param	j an index
* @return	`i` if var was found, `NOT_FOUND` otherwise
*/
int	env_var(char **envp, char *var, int i, int j)
{
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}

/**
* @brief	A function that checks if `var` included in the `arr`
* @param	arr array of arguments
* @param	var search string
* @param	i an index
* @param	j an index
* @return	`i` if var was found, `NOT_FOUND` otherwise
*/
int	arg_var(char **arr, char *var, int i, int j)
{
	while (--i >= 0)
	{
		if (ft_strncmp(arr[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}
