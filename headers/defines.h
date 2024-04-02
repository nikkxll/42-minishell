/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/02 00:52:33 by dshatilo         ###   ########.fr       */
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
	COLON = 58,
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
	CD_LEN = 2,
	ENV_LEN = 3,
	PWD_LEN = 3,
	ECHO_LEN = 4,
	EXIT_LEN = 4,
	UNSET_LEN = 5,
	EXPORT_LEN = 6,
};

enum	e_exit_status
{
	SUCCESS,
  GENERIC_ERROR,
	CMD_ARG_ERROR,
	CMD_PD_FAILURE = 126,
	CMD_NF_FAILURE = 127,
	MALLOC_ERR = 200,
	SYSTEM_ERROR = 201,
	CHDIR_ERROR,
	GETCWD_ERROR,
  EXECVE_FAILURE = 999,
	FORK_FAILURE = 999,
	PIPE_FAILURE = 999,
	DUP_FAILURE = 999,
	DUP_P_FAILURE = 999,
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

# ifndef READ
#  define READ 0
# endif

# ifndef WRITE
#  define WRITE 1
# endif

# ifndef CHILD
#  define CHILD 0
# endif

# ifndef FIRST
#  define FIRST 0
# endif

# ifndef SECOND
#  define SECOND 1
# endif

#endif