/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/01 19:06:28 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"


/*_____ Validate input_____*/
t_bool	validate_input(char *str);
t_bool	validate_and_or(char *str, int *pos);
t_bool	validate_pipeline(char *str, int *pos);
t_bool	validate_command(char *str, int *pos);
t_bool	validate_simple_command(char *str, int *pos);
char	*validate_redirect(char *str);
t_bool	is_word(char c);

enum	e_characters
{
	NULL_TERM,
	NL = 10,
	SPACE = 32,
	D_QUOTE = 34,
	AND = 38,
	S_QUOTE = 39,
	O_ROUND = 40,
	C_ROUND = 41,
	SEMICOLON = 59,
	REDIR_L = 60,
	REDIR_R = 62,
	BACKSLASH = 92,
	PIPE = 124,
};

#endif