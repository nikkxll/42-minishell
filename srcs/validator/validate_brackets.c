/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:51:19 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 17:51:53 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_if_round_brackets_num_is_even(char *str, int point,
	int key, int quote_type)
{
	int	i;

	i = (int)ft_strlen(str) - 1;
	while (i >= point)
	{
		check_if_inside_quotes_with_decr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND)
				key++;
			if (str[i] == C_ROUND)
				key--;
			if (key > 0)
				return (!key);
			i--;
		}
		else
			i--;
	}
	return (!key);
}

int	two_consecutive_round_brackets_check(char *str, int key, int quote_type)
{
	int	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == O_ROUND && str[i + 1] == C_ROUND)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key > 0);
}
