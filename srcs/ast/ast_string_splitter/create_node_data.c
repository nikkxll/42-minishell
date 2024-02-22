/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:46:43 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/22 20:37:21 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

/*
* Function to initialize new node for T_COMMAND type
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success
*/
int	set_node_data_command(t_node_data **node, char *str, int type)
{
	t_node_data	*new_node;
	char		*redir;
	int			status;

	new_node = ft_calloc(1, sizeof(t_node_data));
	if (!new_node)
	{
		*node = new_node;
		return (-1);
	}
	status = modificate_str_command_without_br(str, &redir, 0, 0);
	if (status == -1)
	{
		*node = new_node;
		return (-1);
	}
	new_node->str_left = redir;
	new_node->str_right = str;
	new_node->type = type;
	*node = new_node;
	return (1);
}

/*
* Function to initialize new node for T_AND, T_OR and T_PIPE types
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `point` - shift for the string to point to the beginning of the right part
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success
*/
int	set_node_data_and_or_pipe(t_node_data **node, char *str, int point, int type)
{
	t_node_data	*new_node;

	if (type == T_AND || type == T_OR)
	{
		str[point] = NULL_TERM;
		str[point - 1] = NULL_TERM;
	}
	else
		str[point] = NULL_TERM;
	new_node = ft_calloc(1, sizeof(t_node_data));
	if (!new_node)
	{
		*node = new_node;
		return (-1);
	}
	new_node->str_left = str;
	new_node->str_right = str + point + 1;
	new_node->type = type;
	*node = new_node;
	return (1);
}

/*
* Function to initialize new node for T_BRACKET type
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success
*/
int	set_node_data_bracket(t_node_data **node, char *str, int type)
{
	t_node_data	*new_node;
	char		*first;
	char		*last;

	new_node = ft_calloc(1, sizeof(t_node_data));
	if (!new_node)
	{
		*node = new_node;
		return (-1);
	}
	first = ft_strchr(str, O_ROUND);
	last = ft_strrchr(str, C_ROUND);
	*first = ' ';
	*last = '\0';
	new_node->str_left = str;
	new_node->str_right = NULL;
	new_node->type = type;
	*node = new_node;
	return (1);
}

/*
* Function to initialize new node for T_COMMAND_BR type
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success
*/
int	set_node_data_command_br(t_node_data **node, char *str, int type)
{
	t_node_data	*new_node;
	char		*first;
	int			i;

	i = 0;
	new_node = ft_calloc(1, sizeof(t_node_data));
	if (!new_node)
	{
		*node = new_node;
		return (-1);
	}
	new_node->str_left = command_part(str, &i, 0) + i;
	first = ft_strchr(str, O_ROUND);
	*first = ' ';
	new_node->str_right = str;
	new_node->type = type;
	*node = new_node;
	return (1);
}

/*
* Function to initialize new node for T_CMD_SIMPLE type
*
* Input:
* - `node` - new node to embed into the Abstract Syntax Tree (AST) structure
* - `str` - string that coming from readline function
* - `type` - current meta character type
* 
* Output:
* - `-1` if malloc error occurs, `1` if success
*/
int	set_node_cmd_simple(t_node_data **node, char *str, int type)
{
	t_node_data	*new_node;
	new_node = ft_calloc(1, sizeof(t_node_data));
	if (!new_node)
	{
		*node = new_node;
		return (-1);
	}
	new_node->str_left = str;
	new_node->str_right = NULL;
	new_node->type = type;
	*node = new_node;
	return (1);
}
