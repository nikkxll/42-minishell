/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:46:43 by dnikifor          #+#    #+#             */
/*   Updated: 2024/04/07 04:54:10 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
 * @brief	Function to initialize an intermediate node for @c `T_COMMAND` type
 * @param	info intermediate node to embed into the Abstract Syntax Tree (AST)
 * structure
 * @param	str string that coming from readline function
 * @param	type current meta character type
 * @return	@c `-1` if malloc error occurs, @c `1` if success
 */
int	set_node_info_command(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*redir;
	int			status;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	change_all_redirs_within_quotes(str, 1, 0, 0);
	status = modificate_str_command_without_br(str, &redir, 0, 0);
	if (status == -1)
	{
		free(node_info);
		return (-1);
	}
	change_all_redirs_within_quotes(str, -1, 0, 0);
	node_info->str_left = redir;
	node_info->str_right = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}

/**
 * @brief	Function to initialize an intermediate node for @c `T_AND`,
 * @c `T_OR` and @c `T_PIPE` types
 * @param	info intermediate node to embed into the Abstract Syntax Tree (AST)
 * structure
 * @param	str string that coming from readline function
 * @param	point shift for the string to point to the beginning of the
 * right part
 * @param	type current meta character type
 * @return	@c `-1` if malloc error occurs, @c `1` if success
 */
int	set_node_info_and_or_pipe(t_node_info **info, char *str,
	int point, int type)
{
	t_node_info	*node_info;

	if (type == T_AND || type == T_OR)
	{
		str[point] = NULL_TERM;
		str[point - 1] = NULL_TERM;
	}
	else
		str[point] = NULL_TERM;
	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	node_info->str_left = str;
	node_info->str_right = str + point + 1;
	node_info->type = type;
	*info = node_info;
	return (1);
}

/**
 * @brief	Function to initialize an intermediate node for @c `T_BRACKET`
 * type
 * @param	info intermediate node to embed into the Abstract Syntax Tree (AST)
 * structure
 * @param	str string that coming from readline function
 * @param	type current meta character type
 * @return	@c `-1` if malloc error occurs, @c `1` if success
 */
int	set_node_info_bracket(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*first;
	char		*last;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	first = ft_strchr(str, O_ROUND);
	last = ft_strrchr(str, C_ROUND);
	*first = ' ';
	*last = '\0';
	node_info->str_left = str;
	node_info->str_right = NULL;
	node_info->type = type;
	*info = node_info;
	return (1);
}

/**
 * @brief	Function to initialize an intermediate node for @c `T_COMMAND_BR`
 * type
 * @param	info intermediate node to embed into the Abstract Syntax
 * Tree (AST) structure
 * @param	str string that coming from readline function
 * @param	type current meta character type
 * @return	@c `-1` if malloc error occurs, @c `1` if success
*/
int	set_node_info_command_br(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*first;
	char		*redir;
	char		*left;
	int			i;

	i = 0;
	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	left = command_part(str, &i, 0) + i;
	change_all_redirs_within_quotes(left, 1, 0, 0);
	if (modificate_str_command_without_br(left, &redir, 0, 0) == -1)
	{
		free(node_info);
		return (-1);
	}
	change_all_redirs_within_quotes(left, -1, 0, 0);
	first = ft_strchr(str, O_ROUND);
	*first = ' ';
	node_info->str_left = redir;
	node_info->str_right = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}

/**
* @brief	Function to initialize an intermediate node for @c `T_COMMAND`
* type without redirects
* @param	info intermediate node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	type current meta character type
* @return	@c `-1` if malloc error occurs, @c `1` if success
*/
int	set_node_cmd_simple(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
		return (-1);
	node_info->str_left = NULL;
	node_info->str_right = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}
