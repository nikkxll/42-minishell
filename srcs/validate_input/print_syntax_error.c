/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:31:52 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/08 17:47:05 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_err_token(char *str);

void	print_syntax_error(char *str)
{
	int	i;

	i = 0;
	str = get_err_token(str);
	if (*str == NULL_TERM || *str == NL)
		str = "newline";
	else if (ft_strncmp("||", str, 2) == 0 || ft_strncmp("&&", str, 2) == 0
		|| ft_strncmp(">>", str, 2) == 0 || ft_strncmp("<<", str, 2) == 0)
		i = 2;
	else if (*str == PIPE || *str == O_ROUND || *str == C_ROUND
		|| *str == REDIR_L || *str == REDIR_R)
		i = 1;
	else if (ft_isalnum(*str) == 1 || *str == S_QUOTE || *str == D_QUOTE)
		while (ft_isalnum(str[i]) == 1
			|| str[i] == S_QUOTE || str[i] == D_QUOTE)
			i++;
	if (i != 0)
		str[i] = NULL_TERM;
	ft_putstr_fd("e-bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}

static char	*get_err_token(char *str)
{
	if (ft_strncmp("||", str, 2) == 0 || ft_strncmp("&&", str, 2) == 0
		|| ft_strncmp(">>", str, 2) == 0 || ft_strncmp("<<", str, 2) == 0)
		str += 2;
	else if (*str == PIPE || *str == O_ROUND || *str == C_ROUND
		|| *str == REDIR_L || *str == REDIR_R)
		str++;
	else if (ft_isalnum(*str) == 1)
		while (ft_isalnum(*str) == 1)
			str++;
	while (*str == SPACE)
		str++;
	return (str);
}
