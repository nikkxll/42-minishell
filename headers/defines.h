/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/01 12:50:40 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

enum	e_types
{
	T_ERR,
	T_STRING_ERR,
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

enum	e_validator
{
	PRE_VALIDATION,
	PART_VALIDATION
};

enum	e_errors
{
	MALLOC_FAILURE = 256,
	BRACKETS_NUM_ERROR,
	QUOTES_NUM_ERROR,
	BRACKETS_SYNTAX_ERROR,
	BRACKETS_ARGS_SYNTAX_ERROR,
	META_SYNTAX_ERROR,
	META_NL_ERROR,
	META_PATTERN_ERROR,
	BACKSLASH_SEMICOLON_ERROR
};

#endif