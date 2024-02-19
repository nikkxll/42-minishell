/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/19 13:34:04 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

enum	e_types
{
	T_AND,
	T_OR,
	T_PIPE,
	T_CMD,
	T_REDIR_LL,
	T_REDIR_RR,
	T_REDIR_L,
	T_REDIR_R
};

enum	e_characters
{
	NULL_TERM,
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
	PIPE = 124
};

enum	e_validator
{
	VALID,
	INVALID
};

# ifndef MALLOC_FAILURE
#  define MALLOC_FAILURE 256
# endif

#endif