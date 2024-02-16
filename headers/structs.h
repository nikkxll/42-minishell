/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:24:21 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_node_data
{
	int		type;
	char	*str_left;
	char	*str_right;
}	t_node_data;

typedef struct s_node
{
	int				type;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_and
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_and;

typedef struct s_or
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_or;

typedef struct s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe;

typedef struct s_redir_l
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_redir_l;

typedef struct s_redir_r
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_redir_r;

typedef struct s_redir_ll
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_redir_ll;

typedef struct s_redir_rr
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_redir_rr;

typedef struct s_cmd
{
	int		type;
	char	**cmd;
}	t_cmd;

#endif