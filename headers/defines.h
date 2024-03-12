/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/20 21:34:22 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

enum	e_types
{
	T_AND,
	T_OR,
	T_PIPE,
	T_BRACKET,
	T_COMMAND_BR,
	T_COMMAND,
	T_CMD_SIMPLE,
	T_REDIR
};

enum	e_characters
{
	NULL_TERM,
	NL = 10,
	SPACE = 32,
	D_QUOTE = 34,
	D_SIGN = 36,
	AND = 38,
	S_QUOTE = 39,
	O_ROUND = 40,
	C_ROUND = 41,
	DASH = 45,
	SEMICOLON = 59,
	REDIR_L = 60,
	EQUAL = 61,
	REDIR_R = 62,
	BACKSLASH = 92,
	UNSCORE = 95,
	PIPE = 124,
};

enum	e_exit_status
{
	SUCCESS,
	MALLOC_ERR = 200,
};

enum	e_export_types
{
	EXPORT_ERROR = 1,
	EXPORT_EDIT,
	EXPORT_ADD,
	EXPORT_SKIP
};

# ifndef NOTHING_TO_EXPAND
#  define NOTHING_TO_EXPAND -2
# endif

# ifndef NOT_FOUND
#  define NOT_FOUND -1
# endif

#endif