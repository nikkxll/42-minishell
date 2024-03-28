/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_core_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:09:14 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/28 20:09:24 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Function that checks if string consists of asterisks only
 * @param	pattern string to check in
 * @return	@c `true` if yes, @c `false` otherwise
 */
t_bool	if_only_asterisk(char *pattern)
{
	while (*pattern)
	{
		if (*pattern++ != '*')
			return (false);
	}
	return (true);
}

/**
 * @brief	Function to check for quotes in a string
 * @note	This function checks if a single or double quote character
 * appears in a string and updates a flag accordingly
 * @param	str The string to check for quotes
 * @param	i Pointer to the index of the current character being checked
 * in the string
 * @param	wc_flag Pointer to an integer flag indicating the status of quotes
 * @return	@c `void`
 */
static void	quote_checker(char *str, int *i, int *wc_flag)
{
	if (str[*i] == S_QUOTE && *wc_flag == 0)
		*wc_flag = 1;
	else if (str[*i] == D_QUOTE && *wc_flag == 0)
		*wc_flag = 2;
	else if ((str[*i] == S_QUOTE && *wc_flag == 1)
		|| (str[*i] == D_QUOTE && *wc_flag == 2))
		*wc_flag = 0;
}

/**
 * @brief	Function to transform strings by replacing specific characters
 * @note	This function transforms a given string by replacing occurrences
 * of a certain character with another specified character
 * @param	line The input string to be transformed
 * @param	pattern The pattern string used for transformation
 * @return	@c `void`
 */
void	string_transform(char *line, char *pattern)
{
	int	wc_flag;
	int	i;

	wc_flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ASTERISK)
			line[i] = SEPARATOR;
		i++;
	}
	i = 0;
	while (pattern[i])
	{
		quote_checker(pattern, &i, &wc_flag);
		if (wc_flag == 1 || wc_flag == 2)
		{
			if (pattern[i] == ASTERISK)
				pattern[i] = SEPARATOR;
		}
		i++;
	}
}

/**
 * @brief   Function to transform strings back by restoring specific characters
 * @note This function transforms a given string back by restoring
 * occurrences of a certain character to their original characters
 * @param	line The input string to be transformed back.
 * @param	pattern The pattern string used for transformation back.
 * @param	res he result of wildcard check.
 * @return	The result of the transformation (res) - unmodified.
 */
t_bool	string_transform_back(char *line, char *pattern, t_bool res)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == SEPARATOR)
			line[i] = ASTERISK;
		i++;
	}
	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == SEPARATOR)
			pattern[i] = ASTERISK;
		i++;
	}
	return (res);
}

/**
 * @brief	Function to determine the length of an array containing
 * entities in the current directory
 * @note	This function opens the current directory, iterates
 * through its contents,
 * and counts the number of entities (files and directories) present
 * @param	sub_arr_len  The length of the sub-array, initialized to 0
 * @return	The length of the array containing entities if successful,
 * or @c `SYSTEM_ERROR` if an error occurs during directory processing
 */
int	array_with_entities_len(int sub_arr_len)
{
	DIR			*dir;
	t_dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Unable to open directory");
		return (SYSTEM_ERROR);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		sub_arr_len++;
		entry = readdir(dir);
	}
	if (closedir(dir) == SYSTEM_ERROR)
	{
		perror("Unable to close directory");
		return (SYSTEM_ERROR);
	}
	if (entry == NULL)
		return (sub_arr_len);
	return (SYSTEM_ERROR);
}
