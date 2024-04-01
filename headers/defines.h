/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/02 00:11:17 by dnikifor         ###   ########.fr       */
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
	SEPARATOR = 31,
	SPACE = 32,
	D_QUOTE = 34,
	D_SIGN = 36,
	AND = 38,
	S_QUOTE = 39,
	O_ROUND = 40,
	C_ROUND = 41,
	ASTERISK = 42,
	DASH = 45,
	DOT = 46,
	SLASH = 47,
	SEMICOLON = 59,
	REDIR_L = 60,
	EQUAL = 61,
	REDIR_R = 62,
	BACKSLASH = 92,
	UNSCORE = 95,
	N_LOWER = 110,
	PIPE = 124,
};

enum	e_builtins
{
	CD_LEN = 3,
	ENV_LEN = 4,
	PWD_LEN = 4,
	ECHO_LEN = 5,
	EXIT_LEN = 5,
	UNSET_LEN = 6,
	EXPORT_LEN = 7,
};

enum	e_exit_status
{
	SUCCESS,
	GENERIC_ERROR,
	CMD_ARG_ERROR,
	MALLOC_ERR = 200,
	SYSTEM_ERROR = 201,
};

enum	e_export_types
{
	EXPORT_ERROR = 1,
	EXPORT_EDIT,
	EXPORT_ADD,
	EXPORT_SKIP
};

enum	e_wc_paths
{
	NO_PATH = 1,
	DOT_PATH,
	ABS_PATH,
};

# ifndef NOTHING_TO_EXPAND
#  define NOTHING_TO_EXPAND -2
# endif

# ifndef NOT_FOUND
#  define NOT_FOUND -1
# endif

#endif