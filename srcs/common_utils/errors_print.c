/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:52 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/06 13:51:06 by dshatilo         ###   ########.fr       */
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
 * @brief	A function that prints an warning for shlvl var change
 * @param	number number corresponding to the shlvl
 * @return	@c `void`
 */
void	shlvl_warning(int number)
{
	char	*first_part;
	char	*num;
	char	*first_num_part;
	char	*msg;

	first_part = "\033[0;31me-bash: \033[0;0mwarning: minishell level (";
	num = ft_itoa(number);
	if (!num)
		return ;
	first_num_part = ft_strjoin(first_part, num);
	free(num);
	if (!first_num_part)
		return ;
	msg = ft_strjoin(first_num_part, ") too high, resetting to 1\n");
	free(first_num_part);
	if (!msg)
		return ;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

/**
 * @brief	A function that prints an error without any arguments in it
 * @param	cmd command
 * @param	msg error message
 * @return	@c `void`
 */
void	perror_err_msg(char *cmd, char *arg)
{
	cmd = ft_strjoin("\033[0;31me-bash: \033[0;0m", cmd);
	if (!cmd)
		return ;
	arg = ft_strjoin(cmd, arg);
	free(cmd);
	if (!arg)
		return ;
	perror(arg);
	free(arg);
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
