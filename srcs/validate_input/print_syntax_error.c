/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:31:52 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/27 11:19:22 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief	Handles printing syntax error messages for unexpected tokens
 * @note	This function prints a syntax error message indicating unexpected
 * tokens in a given string. It identifies the type of token and modifies the
 * string to null-terminate at the token position,
 * then prints the error message
 * @param	str String representing the unexpected token
 * @return	@c `void`
 */
void	print_syntax_error(char *str)
{
	int	i;

	i = 0;
	if (*str == NULL_TERM)
		str = "newline";
	else if (ft_strncmp("||", str, 2) == 0 || ft_strncmp("&&", str, 2) == 0
		|| ft_strncmp(">>", str, 2) == 0 || ft_strncmp("<<", str, 2) == 0)
		i = 2;
	else if (*str == PIPE || *str == O_ROUND || *str == C_ROUND
		|| *str == REDIR_L || *str == REDIR_R || *str == AND)
		i = 1;
	else if (ft_isalnum(*str) == 1 || *str == S_QUOTE || *str == D_QUOTE)
		while (ft_isalnum(str[i]) == 1
			|| str[i] == S_QUOTE || str[i] == D_QUOTE)
			i++;
	if (i != 0)
		str[i] = NULL_TERM;
	ft_putstr_fd("e-bash: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
