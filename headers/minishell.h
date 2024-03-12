/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/11 20:28:15 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"

#include <stdio.h>

/*_____ Built-ins _____*/
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

/*_____ Dollar-sign-expansion _____*/
int				expand_dollar_sign(char **str, char **envp, int last_part_ind);

/*_____ Validate-input _____*/
t_bool	validate_input(char *str);
char	*validate_and_or(char *str, t_bool *status);
char	*validate_pipeline(char *str, t_bool *status);
char	*validate_command(char *str, t_bool *status);
char	*validate_simple_command(char *str, t_bool *status);
char	*validate_redirect(char *str, t_bool *status);
char	*validate_word(char *str, t_bool *status);
t_bool	is_blank_string(char *str);
void	print_syntax_error(char *str);

#endif