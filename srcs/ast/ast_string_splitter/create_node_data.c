/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:46:43 by dnikifor          #+#    #+#             */
/*   Updated: 2024/03/12 12:36:34 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/**
* @brief	Function to initialize new node for T_COMMAND type
* @param	info new node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	type current meta character type
* @return	`-1` if malloc error occurs, `1` if success
*/
int	set_node_info_command(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*redir;
	int			status;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
	{
		*info = node_info;
		return (-1);
	}
	status = modificate_str_command_without_br(str, &redir, 0, 0);
	if (status == -1)
	{
		*info = node_info;
		return (-1);
	}
	node_info->str_left = redir;
	node_info->str_right = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}

/**
* @brief	Function to initialize new node for T_AND, T_OR and T_PIPE types
* @param	info new node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	point shift for the string to point to the beginning of the
* right part
* @param	type current meta character type
* 
* @return	`-1` if malloc error occurs, `1` if success
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
	{
		*info = node_info;
		return (-1);
	}
	node_info->str_left = str;
	node_info->str_right = str + point + 1;
	node_info->type = type;
	*info = node_info;
	return (1);
}

/**
* @brief	Function to initialize new node for T_BRACKET type
* @param	info new node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	type current meta character type
* @return	`-1` if malloc error occurs, `1` if success
*/
int	set_node_info_bracket(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*first;
	char		*last;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
	{
		*info = node_info;
		return (-1);
	}
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
* @brief	Function to initialize new node for T_COMMAND_BR type
* @param	info new node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	type current meta character type
* @return	`-1` if malloc error occurs, `1` if success
*/
int	set_node_info_command_br(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;
	char		*first;
	int			i;

	i = 0;
	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
	{
		*info = node_info;
		return (-1);
	}
	node_info->str_left = command_part(str, &i, 0) + i;
	first = ft_strchr(str, O_ROUND);
	*first = ' ';
	node_info->str_right = str;
	node_info->type = type;
	*info = node_info;
	return (1);
}

/**
* @brief	Function to initialize new node for T_CMD_SIMPLE type
* @param	info new node to embed into the Abstract Syntax Tree (AST)
* structure
* @param	str string that coming from readline function
* @param	type current meta character type
* @return	`-1` if malloc error occurs, `1` if success
*/
int	set_node_cmd_simple(t_node_info **info, char *str, int type)
{
	t_node_info	*node_info;

	node_info = ft_calloc(1, sizeof(t_node_info));
	if (!node_info)
	{
		*info = node_info;
		return (-1);
	}
	node_info->str_left = str;
	node_info->str_right = NULL;
	node_info->type = type;
	*info = node_info;
	return (1);
}
