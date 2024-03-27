/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/27 16:14:40 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"

#include <stdio.h>

/*_____ Readline _____*/
void			rl_clear_history(void);
void			rl_replace_line(const char *text, int clear_undo);

/*_____ Validate-input _____*/
t_bool			validate_input(char *str);
char			*validate_and_or(char *str, t_bool *status);
char			*validate_pipeline(char *str, t_bool *status);
char			*validate_command(char *str, t_bool *status);
char			*validate_simple_command(char *str, t_bool *status);
char			*validate_redirect(char *str, t_bool *status);
char			*validate_word(char *str, t_bool *status);
t_bool			is_blank_string(char *str);
void			print_syntax_error(char *str);

/*_____ Create-tree _____*/
t_and			*init_t_and(void);
t_or			*init_t_or(void);
t_pipe			*init_t_pipe(void);
t_bracket		*init_t_bracket(void);
t_command		*init_t_command(void);
t_command_br	*init_t_command_br(void);
t_cmd_simple	*init_t_cmd_simple(void);
t_redir			*init_t_redir(void);
t_bool			create_tree(char *str, t_node **root);
t_bool			create_node(t_node_info *data, t_node **base);
void			free_tree(t_node **root);
t_bool			add_and_or_pipe_trees(t_node_info *data, t_node **root);
t_bool			add_bracket(t_node_info *data, t_node **root);
t_bool			add_command(t_node_info *data, t_node **root);
t_bool			add_command_br(t_node_info *data, t_node **root);
t_bool			add_cmd_simple(t_node_info *data, t_node **root);

/*_____ String-splitter _____*/
int				set_node_info_and_or_pipe(t_node_info **node, char *str,
					int point, int type);
int				set_node_info_command_br(t_node_info **node, char *str,
					int type);
int				set_node_info_command(t_node_info **node, char *str, int type);
int				set_node_info_bracket(t_node_info **node, char *str, int type);
int				set_node_cmd_simple(t_node_info **node, char *str, int type);
int				and_if_condition_block(t_node_info **node, char *str, int type,
					int i);
int				string_splitter(t_node_info **node, char *str, int type,
					int i);
t_bool			is_odd(int number);
void			check_if_inside_quotes(char *str, int *i, int *quote_type);
int				round_brackets_check(char *str, int point);
int				quote_check(char *str, int point, int symbol);
int				first_nonspace_char_is_bracket(char *str);
int				last_nonspace_char_is_bracket(char *str);
char			*command_part(char *str, int *i, int quote_type);
int				modificate_str_command_without_br(char *str, char **redir,
					int i, int j);
int				and_if_condition_block(t_node_info **node, char *str, int type,
					int i);
int				pipe_block(t_node_info **node, char *str, int type, int i);
int				brackets_block(t_node_info **node, char *str, int type);
int				command_block(t_node_info **node, char *str, int type);
int				command_without_bracket_block(t_node_info **node, char *str,
					int type);
int				brackets_search(char *str);
int				redir_search(char *str);

/*_____ Execution _____*/

int				expand_dollar_sign(char **str, char **envp, int last_part_ind);
int				environment_search_exp_module(char **envp, char *var, int i,
					int j);
void			index_quotes(char *str, int i, int *single_q, int *double_q);

int				command_run(char **arr, char ***envp);
char			**sort_string_arr(char **argv, int size);
char			**cpy_env(char **envp);
void			remove_quotes(char *str, int i, int j);
void			skip_characters(char *str, int *i, int symbol);
void			processing(char **arr, int i);
int				env_var(char **envp, char *var, int i, int j);
int				arg_var(char **arr, char *var, int i, int j);
t_bool			ft_isenv(char c, int *j);
void			print_error_with_arg(char *error, char *arg, char *cmd);
void			print_error(char *error, char *cmd);
int				run_cd(char **arr, char **envp);
int				run_echo(char **arr, int i, int j, int nl_flag);
int				run_export(char **arr, char ***envp);
void			create_operations_array(char **arr, char **envp,
					int *operations);
int				check_operations(int *operations, int *i, int *j, int type);
void			execute_error(char **arr, int *operations);
int				edit_env_list(char ***new_env, char **arr, int *operations);
int				add_to_env_list(char ***new_env, char **arr, char **envp,
					int *operations);
int				run_pwd(char **arr);
int				run_unset(char **arr, char ***envp);
int				run_env(char **arr, char ***envp);
int				run_exit(char **arr);

char			**wrapper_ft_split_with_quotes(char *str);

int				allocate_temp_array(char ***arr, t_w_cards *wc);
int				fill_temp_array(char ***arr, t_w_cards *wc);
int				allocate_and_fill_expanded_array(t_w_cards *wc);
char			**str_array_join(char **arr, char *str);
int				sort_array_with_command_inside(t_w_cards *wc, char ***arr);
int				array_sorting_process(t_w_cards *wc, int *i);
t_bool			if_only_asterisk(char *pattern);
void			string_transform(char *line, char *pattern);
t_bool			string_transform_back(char *line, char *pattern,
					t_bool res);
int				array_with_entities_len(int sub_arr_len);
t_bool			wildcard_strcmp(char *line, char *pattern);
int				entities_expand(char ***temp_arr, char *str, t_w_cards *wc);
int				wildcards(char ***arr);

int				minishell(char **arr, char ***env);

#endif