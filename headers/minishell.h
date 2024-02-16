/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/16 13:42:39 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"
#include <stdio.h>

t_and		*init_t_and(void);
t_or		*init_t_or(void);
t_pipe		*init_t_pipe(void);
t_cmd		*init_t_cmd(void);
t_redir_l	*init_t_redir_l(void);
t_redir_r	*init_t_redir_r(void);
t_redir_ll	*init_t_redir_ll(void);
t_redir_rr	*init_t_redir_rr(void);

void		free_node_data(t_node_data *data);

#endif