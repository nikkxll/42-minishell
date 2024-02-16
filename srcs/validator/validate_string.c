/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:53:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/16 23:40:01 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

int	quotes_validator_check(char *str, int len, int type)
{
	int	i;
	int	key;

    i = 0;
	key = 0;
	while (i < len)
	{
		if (str[i] == type)
            key++;
        i++;
	}
	return (key % 2);
}

int validator(char *str)
{
    if (round_brackets_check(str, 0) &&
        !quotes_validator_check(str, (int)ft_strlen(str), D_QUOTE) &&
        !quotes_validator_check(str, (int)ft_strlen(str), S_QUOTE))
        return (1);
    else
        return (0);
}

int main(void)
{
    char str[1000] = "\"(cmd || file) < cmd << cmd\" (cmd || cmd)\"";
    printf("%d\n", validator(str));
}
