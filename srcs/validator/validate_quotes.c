/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:49:58 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 17:51:41 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_if_quotes_num_is_even(char *str, int type, int key, int quote_type)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_strlen(str);
	while (i < len)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == type)
				key++;
			i++;
		}
		else
			i++;
	}
	return (key % 2);
}
