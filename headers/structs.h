/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/22 10:49:11 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <dirent.h>

typedef struct dirent	t_dirent;

typedef struct s_wildcards
{
	DIR			*dir;
	t_dirent	*entry;
	char		***temp_arr;
	char		**new_arr;
	int			arr_len;
	int			ent_len;
	int			status;
}	t_w_cards;

typedef struct s_dollar_exp
{
	char	*env_part;
	int		i;
	int		k;
	int		single_q;
	int		double_q;
	int		last_part_ind;
	int		env_list_pos;
}	t_dollar_exp;

typedef struct s_node
{
	int				type;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_node_info
{
	int		type;
	char	*str_left;
	char	*str_right;
}	t_node_info;

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

typedef struct s_bracket
{
	int		type;
	t_node	*left;
}	t_bracket;

typedef struct s_command
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_command;

typedef struct s_command_br
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_command_br;

typedef struct s_cmd_simple
{
	int		type;
	char	*cmd;
}	t_cmd_simple;

typedef struct s_redir
{
	int		type;
	char	*str;
}	t_redir;

#endif