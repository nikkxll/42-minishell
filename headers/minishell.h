/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/02/20 19:06:42 by dnikifor         ###   ########.fr       */
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


//validator

void		remove_quotes(char *str);
int			check_if_round_brackets_num_is_even(char *str, int point, int key,
				int quote_type);
int			two_consecutive_round_brackets_check(char *str, int key,
				int quote_type);
int			check_if_redirect_file_pattern_complied(char *str, int quote_type,
				int i);
int			check_if_redirects_and_or_are_correct(char *str, int first,
				int second, int quote_type);
int			check_if_quotes_num_is_even(char *str, int type, int key,
				int quote_type);
void		check_if_inside_quotes_with_decr(char *str, int *i,
				int *quote_type);
void		check_if_inside_quotes_with_incr(char *str, int *i,
				int *quote_type);
int			check_if_backslash_or_semicolon_exist(char *str, int quote_type);

//ast_string_splitter

int			set_node_data(t_node_data **node, char *str, int point, int type);
int			set_node_data_compound_with_brackets(t_node_data **node, char *str,
				int point, int type);
int			and_if_condition_block(t_node_data **node, char *str, int type,
				int i);
int			parenthesis_quotes_checker(t_node_data **node, char *str, int type,
				int i);
t_bool		if_odd(int number);
int			round_brackets_check(char *str, int point);
int			quote_check(char *str, int point, int symbol);
int			first_nonspace_char_is_quote(char *str);
int			last_nonspace_char_is_quote(char *str);

#endif