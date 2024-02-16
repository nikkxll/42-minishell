/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:12:25 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/16 12:09:08 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum	e_types
{
	T_AND,
	T_OR,
	T_PIPE,
	T_REDIR_LL,
	T_REDIR_RR,
	T_REDIR_L,
	T_REDIR_R,
	CMD
};

enum	e_parenthesis
{
	S_QUOTE,
	D_QUOTE,
	ROUND,
};

typedef struct s_node_data
{
	int		type;
	char	*str_left;
	char	*str_right;
}	t_node_data;