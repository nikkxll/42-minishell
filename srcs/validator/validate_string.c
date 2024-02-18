/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:53:24 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/18 13:07:16 by dnikifor         ###   ########.fr       */
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
		if (key > 0)
			return (!key);
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

int	two_conseq_round_brackets_check(char *str)
{
	int	i;
	int	key;

    i = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		if (str[i] == O_ROUND && str[i + 1] == C_ROUND)
            key++;
        i++;
	}
	return (key > 0);
}

int	redirect_format_check(char *str)
{
	int	i;
	int	key;

    i = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		if ((str[i] == REDIR_R && str[i + 1] == REDIR_L)
			|| (str[i] == REDIR_L && str[i + 1] == REDIR_R))
			return (INVALID);
		if ((str[i] == REDIR_R && str[i + 1] == REDIR_R)
			|| (str[i] == REDIR_L && str[i + 1] == REDIR_L))
		{
			if (str[i + 2] == REDIR_R || str[i + 2] == REDIR_L)
				return (INVALID);
		}
		i++;
	}
	return (VALID);
}

int redirect_files_check_utils(char *str, int i)
{
	while (str[i] == SPACE && str[i] != NULL_TERM)
		i++;
	if (str[i] == REDIR_R || str[i] == REDIR_L || str[i] == NULL_TERM)
		return (INVALID);
	return (VALID);
}

int	redirect_files_check(char *str)
{
	int	i;
	int	key;

    i = 0;
	key = 0;
	while (str[i] != NULL_TERM)
	{
		if ((str[i] == REDIR_R && str[i + 1] != REDIR_R)
			|| (str[i] == REDIR_L && str[i + 1] != REDIR_L))
			{
				if (redirect_files_check_utils(str, i + 1))
					return (INVALID);
				i += 1;
			}
		else if ((str[i] == REDIR_R && str[i + 1] == REDIR_R)
			|| (str[i] == REDIR_L && str[i + 1] == REDIR_L))
			{
				if (redirect_files_check_utils(str, i + 2))
					return (INVALID);
				i += 2;
			}
		else
			i++;
	}
	return (VALID);
}

int validator(char *str)
{
    if (round_brackets_check(str, 0) &&
        !quotes_validator_check(str, (int)ft_strlen(str), D_QUOTE) &&
        !quotes_validator_check(str, (int)ft_strlen(str), S_QUOTE) &&
		!two_conseq_round_brackets_check(str) &&
		!redirect_format_check(str) &&
		!redirect_files_check(str))
        return (VALID);
    else
        return (INVALID);
}

void remove_quotes(char *str)
{
    int i;
    int j;

	i = 0;
	j = 0;
    while (str[i] != NULL_TERM)
	{
        if ((str[i] == S_QUOTE && str[i + 1] == D_QUOTE
			&& str[i + 2] == D_QUOTE && str[i + 3] == S_QUOTE) ||
			(str[i] == D_QUOTE && str[i + 1] == S_QUOTE
			&& str[i + 2] == S_QUOTE && str[i + 3] == D_QUOTE))
		{
			str[j++] = str[i + 1];
			str[j++] = str[i + 2];
			i += 4;
        }
        else if ((str[i] == S_QUOTE && str[i + 1] == S_QUOTE) ||
			(str[i] == D_QUOTE && str[i + 1] == D_QUOTE))
			i += 2;
		else
			str[j++] = str[i++];
    }
    str[j] = NULL_TERM;
}

int main(void)
{
	int status;
	
    char str[1000] = "echo >>a >a";
	status = validator(str);
	if (status)
    	printf("%s\n", "INVALID");
	else
	{
    	printf("%s\n", "VALID");
		remove_quotes(str);
		printf("%s\n", str);
	}
}
