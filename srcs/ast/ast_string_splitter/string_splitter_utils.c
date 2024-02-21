/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:43:34 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/21 13:54:58 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

t_bool	if_odd(int number)
{
	return (number % 2);
}

int	round_brackets_check(char *str, int point)
{
	int	i;
	int	key;

	i = (int)ft_strlen(str) - 1;
	key = 0;
	while (i >= point)
	{
		if (str[i] == O_ROUND)
			key++;
		if (str[i] == C_ROUND)
			key--;
		i--;
	}
	return (!key);
}

int	quote_check(char *str, int point, int symbol)
{
	int		i;
	int		pair[2];

	i = (int)ft_strlen(str) - 1;
	pair[0] = 0;
	pair[1] = 0;
	while (i >= point)
	{
		if (str[i] == symbol)
			pair[0]++;
		i--;
	}
	while (--point > 0)
	{
		if (str[point] == symbol)
			pair[1]++;
	}
	return (if_odd(pair[0]) == false && if_odd(pair[1]) == false);
}

int	first_nonspace_char_is_quote(char *str)
{
	int		i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		while (str[i] == SPACE)
			i++;
		if (str[i] == O_ROUND)
			return (1);
		else
			return (0);
	}
	return (0);
}

int	last_nonspace_char_is_quote(char *str)
{
	int		i;

	i = (int)ft_strlen(str) - 1;
	while (i >= 0)
	{
		while (str[i] == SPACE)
			i--;
		if (str[i] == C_ROUND)
			return (1);
		else
			return (0);
	}
	return (0);
}
