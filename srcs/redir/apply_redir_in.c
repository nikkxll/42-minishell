/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:03:41 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 01:52:44 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_bool	remove_last_slash(char **s);
static int		check_access_in(char *redir, char *str);

int	apply_redir_in(char *str, t_minishell *ms, int *in)
{
	int		status;
	char	*redir;

	close(*in);
	str = ft_strdup(str);
	(void)in;
	(void)ms;
	status = check_redir(&str, ms);
	if (status != 0)
		return (status);
	redir = ft_strdup(str);
	if (!redir)
	{
		free(str);
		return (MALLOC_ERR);
	}
	remove_slashes(&redir);
	status = check_access_in(redir, str);
	//add open part;
	free(redir);
	free(str);
	return (status);
}


static int	check_access_in(char *redir, char *str)
{
	struct stat	info;
	t_bool		has_slash;

	has_slash = remove_last_slash(&redir);
	if (access(redir, F_OK) == -1)
	{
		print_err_msg(str, ": No such file or directory\n");
		return (GENERIC_ERROR);
	}
	if (stat(redir, &info) == -1)
		return (STAT_FAILURE);
	if (has_slash == true && S_ISDIR(info.st_mode) == false)
	{
		print_err_msg(str, ": Not a directory\n");
		return (GENERIC_ERROR);
	}
	if ((info.st_mode & S_IRUSR) == 0)
	{
		print_err_msg(str, ": Permission denied\n");
		return (GENERIC_ERROR);
	}
	return (0);
}

static t_bool	remove_last_slash(char **s)
{
	t_bool	has_slash;
	int		len;
	char	*str;

	str = *s;
	has_slash = false;
	len = ft_strlen(str);
	if (len != 0)
		has_slash = (str[len - 1] == SLASH);
	if (has_slash == true)
		str[len - 1] = NULL_TERM;
	return (has_slash);
}


// int	apply_redir_in(char	*str)
// {
// 	char	*redir;
// 	int		len;
// 	t_bool	has_slash;
// 	int		status;

// 	redir = ft_strdup(str);
// 	if (!redir)
// 		return (MALLOC_ERR);
// 	remove_slashes(&redir);
// 	has_slash = false;
// 	len = ft_strlen(redir);
// 	if (len != 0)
// 		has_slash = (redir[len - 1] == SLASH);
// 	if (has_slash == true)
// 		redir[len - 1] = NULL_TERM;
// 	status = check_access_in(redir, has_slash, str);
// 	free(redir);
// 	return (status);
// }

// int	check_access_in(char *redir, t_bool has_slash, char *str)
// {
// 	struct stat	info;

// 	if (access(redir, F_OK) == -1)
// 	{
// 		print_err_msg(str, ": No such file or directory\n");
// 		return (GENERIC_ERROR);
// 	}
// 	if (stat(redir, &info) == -1)
// 		return (STAT_FAILURE);
// 	if (has_slash == true && S_ISDIR(info.st_mode) == false)
// 	{
// 		print_err_msg(str, ": Not a directory\n");
// 		return (GENERIC_ERROR);
// 	}
// 	if ((info.st_mode & S_IRUSR) == 0)
// 	{
// 		print_err_msg(str, ": Permission denied\n");
// 		return (GENERIC_ERROR);
// 	}
// 	return (0);
// }