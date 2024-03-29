/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/29 14:10:49 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
* @brief	A function that prints an error without any arguments in it
* @param	cmd command
* @param	msg error message
* @return	@c `void`
*/
void	print_err_msg(char *cmd, char *msg)
{
	cmd = ft_strjoin("\033[0;31me-bash: \033[0;0m", cmd);
	if (!cmd)
		return ;
	msg = ft_strjoin(cmd, msg);
	free(cmd);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

/**
* @brief	A function that prints an error with an argument in it
* @param	cmd command
* @param	arg argument
* @param	msg error message
* @return	@c `void`
*/
void	print_arg_err_msg(char *cmd, char *arg, char *msg)
{
	cmd = ft_strjoin("\033[0;31me-bash: \033[0;0m", cmd);
	if (!cmd)
		return ;
	arg = ft_strjoin(cmd, arg);
	free(cmd);
	if (!arg)
		return ;
	msg = ft_strjoin(arg, msg);
	free(arg);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

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
	ft_putstr_fd("\033[0;31me-bash: \033[0;0msyntax error near "
		"unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
