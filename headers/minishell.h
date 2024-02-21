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
int			set_node_data_command_with_brackets(t_node_data **node, char *str,
				int point, int type);
int			set_node_data_command_without_brackets(t_node_data **node,
				char *str, int point, int type);
int			and_if_condition_block(t_node_data **node, char *str, int type,
				int i);
int			parenthesis_quotes_checker(t_node_data **node, char *str, int type,
				int i);
t_bool		if_odd(int number);
int			round_brackets_check(char *str, int point);
int			quote_check(char *str, int point, int symbol);
int			first_nonspace_char_is_quote(char *str);
int			last_nonspace_char_is_quote(char *str);
char		*command_part(char *str, int *i, int *j, int quote_type);
int			modificate_str_command_without_br(char *str, char **redir, int i,
				int j);
int			and_if_condition_block(t_node_data **node, char *str, int type,
				int i);
int			pipe_block(t_node_data **node, char *str, int type, int i);
int			brackets_block(t_node_data **node, char *str, int type, int i);
int			command_block(t_node_data **node, char *str, int type, int i);
int			command_without_bracket_block(t_node_data **node, char *str,
				int type, int i);
int			brackets_search(char *str);
int			redir_search(char *str);
int		ft_error(char *message, int code);

#endif