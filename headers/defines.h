/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:11:31 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:16:20 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

enum	e_types
{
	T_AND,
	T_OR,
	T_PIPE,
	T_REDIR_LL,
	T_REDIR_RR,
	T_REDIR_L,
	T_REDIR_R,
	T_CMD
};

enum	e_parenthesis
{
	S_QUOTE,
	D_QUOTE,
	ROUND,
};

# ifndef MALLOC_FAILURE
#  define MALLOC_FAILURE 256
# endif

#endif