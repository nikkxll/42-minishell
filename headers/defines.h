/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/18 13:06:20 by dnikifor         ###   ########.fr       */
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
	REDIR_L = 60,
	REDIR_R = 62,
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