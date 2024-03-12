/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:54 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/10 01:13:43 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"
/**
* @brief	Removes consecutive quotes from the string is allowable
* @param	str - string that coming from readline function
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

void	skip_characters(char *str, int *i, int symbol)
{
	while (str[*i] == symbol && str[*i] != NULL_TERM)
		(*i)++;
}

void	processing(char **arr, int i)
{
	while (arr[i])
		remove_quotes(arr[i++], 0, 0);
}

int	env_var(char **envp, char *var, int i, int j)
{
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}

int	arg_var(char **arr, char *var, int i, int j)
{
	while (--i >= 0)
	{
		if (ft_strncmp(arr[i], var, j) == 0)
			return (i);
	}
	return (NOT_FOUND);
}
