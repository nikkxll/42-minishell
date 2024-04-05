/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 18:35:24 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"

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
t_redir			*init_t_redir(void);
t_bool			create_tree(char *str, t_node **root);
t_bool			create_node(t_node_info *data, t_node **base);
void			free_tree(t_node **root);
t_bool			add_and_or_pipe_trees(t_node_info *data, t_node **root);
t_bool			add_bracket(t_node_info *data, t_node **root);
t_bool			add_command(t_node_info *data, t_node **root);
t_bool			add_command_br(t_node_info *data, t_node **root);

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

/*_____ Traverse-tree _____*/
int				traverse_tree(t_node **node, t_minishell *ms);
int				traverse_and(t_node **node, t_minishell *ms);
int				traverse_or(t_node **node, t_minishell *ms);
int				traverse_pipe(t_node **node, t_minishell *ms);
int				traverse_bracket(t_node **node, t_minishell *ms);
int				traverse_command_br(t_node **node, t_minishell *ms);
int				traverse_command(char *cmd, char *redir, t_minishell *ms);
int				parse_cmd(char *cmd, char ***res, t_minishell *ms);
int				wait_children(pid_t *pids, int num);
t_bool			is_builtin(char *cmd);
int				locate_command(char	**cmd, char	**envp);
int				find_executable(char **command, char **paths);
int				run_builtin(char **command, char *redir, t_minishell *ms);

/*_____ Redir _____*/
int				apply_redirects(char *redir, t_minishell *ms);
int				check_redir(char **redir, t_minishell *ms);
int				apply_heredoc(char *limiter, int *in);
int				apply_redir_in(char *str, t_minishell *ms, int *in);
int				apply_redir_out(char *redir, t_minishell *ms, int *out);
int				apply_append(char *redir, t_minishell *ms, int *out);
/*_____ Execution _____*/

int				dollar_sign_expansion(char **str, char **envp,
					int last_exit_status);
int				expand_dollar_sign_q_mark(char **str, int last_exit_status);
int				expand_dollar_sign_generic(char **str, char **envp);
int				environment_search_exp_module(char **envp, char *var, int i,
					int j);
void			index_quotes(char *str, int i, int *single_q, int *double_q);

int				command_run(char **arr, t_minishell *ms);
char			**sort_string_arr(char **argv, int size);
char			**cpy_env(char **envp);
void			remove_quotes(char *str, int i, int j);
void			skip_characters(char *str, int *i, int symbol);
void			remove_quotes_arr(char **arr, int i);
int				env_var(char **envp, char *var, int i, int j);
int				arg_var(char **arr, char *var, int i, int j);
t_bool			ft_isenv(char c, int *j);
void			print_err_msg(char *cmd, char *msg);
void			print_arg_err_msg(char *cmd, char *arg, char *msg);
void			perror_err_msg(char *cmd, char *arg);
void			run_cd(char **arr, t_minishell *ms, int status);
void			cd_precheck(char **arr, t_minishell *ms);
void			struct_pwd_and_full_oldpwd_update(char *new_pwd,
					t_minishell *ms);
void			update_env_oldpwd(char ***envp, t_minishell *ms);
void			update_env_pwd(char ***envp, t_minishell *ms);
void			run_echo(char **arr, int i, int j, int nl_flag);
void			run_export(char **arr, t_minishell *ms);
void			create_operations_array(char **arr, char **envp,
					int *operations);
int				check_operations(int *operations, int *i, int *j, int type);
int				execute_other(char **arr, int *operations);
int				edit_env_list(char ***new_env, char **arr, int *operations);
int				add_to_env_list(char ***new_env, char **arr, t_minishell *ms,
					int *operations);
int				add_to_env_list_new_env(char **envp, char ***result,
					int *i, int *len);
void			run_pwd(char **arr, t_minishell *ms);
void			run_unset(char **arr, t_minishell *ms);
void			run_env(char **arr, t_minishell *ms);
void			run_exit(char **arr, t_minishell *ms, long num);

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
int				entities_expand(char ***temp_arr, char *str, t_w_cards *wc,
					char **local);
int				fill_temp_array_conditions_block(t_w_cards *wc,
					char **temp_arr_local, char *str, int *i);
int				if_abs_path(t_w_cards *wc, char *str);
t_bool			if_asterisk_in_arr(char **arr, int i, int j);
int				wildcards(char ***arr);

int				array_build_before_wc(char ***arr, int i, int k, int j);
int				minishell(char **arr, t_minishell *ms);

int				get_current_folder_name(char **folder_name);
int				get_prompt(char *folder_name, char **prompt, char *exit_status);

int				shlvl_init(char ***envp);
int				pwd_init(char ***envp, char **pwd);

int				check_for_non_digits(char *str);

#endif