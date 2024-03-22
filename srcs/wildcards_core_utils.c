/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_core_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:09:14 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/22 11:23:18 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_bool	if_only_asterisk(char *pattern)
{
	while (*pattern)
	{
		if (*pattern++ != '*')
			return (false);
	}
	return (true);
}

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

void	string_quotes_transform(char *line, char *pattern)
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
	remove_quotes(pattern, 0, 0);
}

t_bool	string_quotes_transform_back(char *line, char *pattern, t_bool res)
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
