/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/21 14:46:19 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"

#include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

t_and			*init_t_and(void);
t_or			*init_t_or(void);
t_pipe			*init_t_pipe(void);
t_bracket		*init_t_bracket(void);
t_command		*init_t_command(void);
t_command_br	*init_t_command_br(void);
t_cmd_simple	*init_t_cmd_simple(void);
t_redir			*init_t_redir(void);

t_bool			create_node(t_node_data *data, t_node **base);
void			free_node_data(t_node_data *data);
void			free_tree(t_node **root);

t_bool			add_and_or_pipe_trees(t_node_data *data, t_node **root);
t_bool			add_bracket(t_node_data *data, t_node **root);
t_bool			add_command(t_node_data *data, t_node **root);
t_bool			add_command_br(t_node_data *data, t_node **root);
t_bool			add_cmd_simple(t_node_data *data, t_node **root);

#endif