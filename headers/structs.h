/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:58:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/03 16:36:29 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef struct dirent	t_dirent;

typedef struct s_minishell
{
	char			**env;
	char			*pwd;
	char			*oldpwd;
	unsigned char	exit_status;
	t_bool			is_parent;
}	t_minishell;

typedef struct s_wildcards
{
	DIR			*dir;
	t_dirent	*entry;
	char		***temp_arr;
	char		**new_arr;
	char		**sorted_new_arr;
	char		**final_new_arr;
	int			arr_len;
	int			ent_len;
	int			status;
	int			abs_path_flag;
	t_bool		dot_ind;
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
	t_node	*redir;
	char	*cmd;
}	t_command;

typedef struct s_command_br
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_command_br;

typedef struct s_redir
{
	int		type;
	char	*str;
}	t_redir;

#endif