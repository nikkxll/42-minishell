/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/06 10:57:13 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"


/*_____ Validate input_____*/
t_bool	validate_input(char *str);
char	*validate_and_or(char *str);
char	*validate_pipeline(char *str);
char	*validate_command(char *str);
char	*validate_simple_command(char *str);
char	*validate_redirect(char *str);
char	*validate_word(char *str);
t_bool	is_blank_string(char *str);


char	**sort_string_arr(char **argv, int size);

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