/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/08/23 12:43:49 by dshatilo         ###   ########.fr       */
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
	T_REDIR,
};

enum	e_characters
{
	NULL_TERM,
	HT = 9,
	NL = 10,
	L_REDIR_SEPARATOR = 29,
	R_REDIR_SEPARATOR = 30,
	SEPARATOR = 31,
	SPCE = 32,
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
	Q_MARK = 63,
	BACKSLASH = 92,
	UNSCORE = 95,
	N_LOWER = 110,
	PIPE = 124,
};

enum	e_builtins
{
	NOT_BUILTIN,
	C_EMPTY,
	C_BLANK,
	C_ECHO,
	C_CD,
	C_PWD,
	C_EXPORT,
	C_UNSET,
	C_ENV,
	C_EXIT,
};

enum	e_builtins_len
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
	CMD_PD_FAILURE = 126,
	CMD_NF_FAILURE = 127,
	MALLOC_ERR = 200,
	SYSTEM_ERROR = 201,
	CHDIR_ERROR = 202,
	GETCWD_ERROR = 203,
	UNEXPECTED_EXIT = 255,
	SYNTAX_ERROR = 258,
	EXECVE_FAILURE = 300,
	FORK_FAILURE = 400,
	PIPE_FAILURE = 500,
	DUP_FAILURE = 600,
};

enum	e_export_types
{
	EXPORT_ERROR = 1,
	EXPORT_EDIT,
	EXPORT_ADD,
	EXPORT_SKIP,
};

enum	e_wc_paths
{
	NO_PATH = 1,
	DOT_PATH,
	ABS_PATH,
};

enum	e_signals
{
	DEFAULT,
	INTERACTIVE,
	HEREDOC,
	IGNORE,
};

enum	e_signals_echo
{
	IMPLICIT,
	EXPLICIT,
};

# ifndef PROMPT_STATIC_LEN
#  define PROMPT_STATIC_LEN 12
# endif

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

# ifndef HIST_SIZE
#  define HIST_SIZE 500
# endif

# ifndef HEREDOC_NAME
#  define HEREDOC_NAME "<<.heredoc_"
# endif

#endif