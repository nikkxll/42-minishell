/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/12 20:30:36 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"

typedef struct s_minishell
{
	char			**env;
	char			*pwd;
	char			*oldpwd;
	t_list			*history;
	char			*history_path;
	int				exit_status;
	t_node			*root;
	t_bool			is_parent;
	t_bool			is_oldpwd_unset;
}	t_minishell;


/*_____ Minishell _____*/
void			initialize_minishell(t_minishell **ms);
void			run_minishell(t_minishell **ms);
void			ft_free_minishell(t_minishell *ms);

/*_____ Readline _____*/
void			rl_clear_history(void);
void			rl_replace_line(const char *text, int clear_undo);

/*_____ Validate-input _____*/
int				validate_input(char *str);
char			*validate_and_or(char *str, t_bool *status);
char			*validate_pipeline(char *str, t_bool *status);
char			*validate_command(char *str, t_bool *status);
char			*validate_simple_command(char *str, t_bool *status);
char			*validate_redirect(char *str, t_bool *status);
char			*validate_word(char *str, t_bool *status);

/*_____ Create-tree _____*/
int				create_tree(char *str, t_node **root);
t_bool			create_node(t_node_info *data, t_node **base);
int				add_and_or_pipe_trees(t_node_info *data, t_node **root);
int				add_bracket(t_node_info *data, t_node **root);
int				add_command_br(t_node_info *data, t_node **root);
int				add_command(t_node_info *data, t_node **root);
void			free_tree(t_node **root);
t_and			*init_t_and(void);
t_or			*init_t_or(void);
t_pipe			*init_t_pipe(void);
t_bracket		*init_t_bracket(void);
t_command		*init_t_command(void);
t_command_br	*init_t_command_br(void);
t_redir			*init_t_redir(void);

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
int				lexer(t_node_info **node, char *str, int type,
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
void			change_all_redirs_within_quotes(char *str, int mode, int i,
					int quote_type);

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
int				is_builtin(char *cmd);
int				locate_command(char	**cmd, char	**envp);
int				find_executable(char **command, char **paths);
int				run_builtin(char **command, char *redir, t_minishell *ms,
					int cmd_type);

/*_____ Redir _____*/
int				apply_redirects(char *redir, t_minishell *ms);
int				check_redir(char **redir, t_minishell *ms);
int				apply_heredoc(char *limiter, int *in);
int				apply_redir_in(char *str, t_minishell *ms, int *in);
int				apply_append(char *redir, t_minishell *ms, int *out);
int				apply_redir_out(char *redir, t_minishell *ms, int *out);

/*_____ Execution _____*/
int				dollar_sign_expansion(char **str, char **envp,
					int last_exit_status);
int				expand_dollar_sign_q_mark(char **str, int last_exit_status);
int				expand_dollar_sign_generic(char **str, char **envp);
int				environment_search_exp_module(char **envp, char *var, int i,
					int j);
void			index_quotes(char *str, int i, int *single_q, int *double_q);
int				command_run(char **arr, t_minishell *ms, int cmd_type);
char			**sort_string_arr(char **argv, int size);
char			**cpy_env(char **envp);
void			remove_quotes(char *str, int i, int j);
void			skip_characters(char *str, int *i, int symbol);
void			remove_quotes_arr(char **arr, int i);
int				env_var(char **envp, char *var, int i, int j);
int				arg_var(char **arr, char *var, int i, int j);
t_bool			ft_isenv(char c, int *j);
void			shlvl_warning(int number);
void			run_cd(char **arr, t_minishell *ms, int status);
void			cd_precheck(char **arr, t_minishell *ms);
void			struct_pwd_and_full_oldpwd_update(char *new_pwd,
					t_minishell *ms);
void			update_env_oldpwd(t_minishell *ms);
void			update_env_pwd(t_minishell *ms, int position, char *cwd,
					char *temp);
void			run_echo(char **arr, int i, int j, int nl_flag);
void			run_export(char **arr, t_minishell *ms);
void			create_operations_array(char **arr, char **envp,
					int *operations);
int				check_operations(int *operations, int *i, int *j, int type);
int				execute_other(char **arr, int *operations);
int				edit_env_list(char ***new_env, char **arr, int *operations,
					t_minishell *ms);
int				add_to_env_list(char ***new_env, char **arr, t_minishell *ms,
					int *operations);
int				add_to_env_list_new_env(char **envp, char ***result,
					int *i, int *len);
void			run_pwd(char **arr, t_minishell *ms);
void			run_unset(char **arr, t_minishell *ms);
void			execute_unset(char ***envp, int position, int i);
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
int				shlvl_init(char ***envp);
int				pwd_init(char ***envp, char **pwd);
int				check_for_non_digits(char *str);
int				var_init_when_no_var_exists(char ***envp, int i, char *var);

/*_____ Utils _____*/
void			init_history(t_minishell **minishell);
void			add_ebash_history(char *cmdline, t_minishell **minishell,
					int mode);
void			save_history_to_file(t_minishell *ms);
int				get_prompt(char **prompt, int exit_status);
t_bool			is_blank_string(char *str);
void			print_syntax_error(char *str);
void			print_err_msg(char *cmd, char *msg);
void			print_arg_err_msg(char *cmd, char *arg, char *msg);
void			perror_err_msg(char *cmd, char *arg);
int				handle_ctrl_d(char *prompt);
void			ctrl_d_error_handler(char *msg);

/*_____ Signals _____*/
void			signal_mode_switch(int mode);
void			signal_chars_toggler(int toggle);

/*_____ Clearing _____*/
void			end_process(t_minishell *ms);

#endif