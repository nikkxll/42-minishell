/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:39:03 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/27 15:51:28 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_string(char *s, int fd, ssize_t bytes, int	*status);

char	*ft_get_line(char *str, int	*status);

char	*dealloc(char *s, char *line);

char	*get_next_line(int fd, int *status, char **string)
{
	char		*line;

	*status = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		*status = -1;
		return (NULL);
	}
	*string = check_string(*string, status);
	if (*string == NULL)
		return (NULL);
	*string = get_string(*string, fd, 1, status);
	if (!(*string))
		return (NULL);
	line = ft_get_line(*string, status);
	if (!line)
	{
		*string = ft_free(*string);
		return (NULL);
	}
	*string = dealloc(*string, line);
	return (line);
}

char	*get_string(char *s, int fd, ssize_t bytes, int	*status)
{
	char	buffer[BUFFER_SIZE];

	while ((s && !ft_strchr(s, '\n')) && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			*status = 2;
			free(s);
			return (NULL);
		}
		if (bytes == 0)
		{
			if (*s == 0)
				s = ft_free(s);
			return (s);
		}
		s = add_to_string(s, buffer, bytes);
		if (s == NULL)
			*status = 3;
	}
	return (s);
}

char	*ft_get_line(char *str, int	*status)
{
	char	*line;
	size_t	line_len;

	line_len = 0;
	while (str[line_len] != 0 && str[line_len] != '\n')
		line_len++;
	if (str[line_len] == '\n')
		line_len++;
	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
	{
		*status = 1;
		return (NULL);
	}
	line[line_len] = 0;
	ft_strncpy(line, str, line_len);
	return (line);
}

char	*dealloc(char *s, char *line)
{
	char	*new_s;
	size_t	s_len;
	size_t	n_len;
	size_t	line_len;

	s_len = 0;
	line_len = 0;
	while (line[line_len] != 0)
		line_len++;
	while (s[s_len] != 0)
		s_len++;
	n_len = s_len - line_len;
	if (!n_len)
		return (ft_free(s));
	new_s = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!new_s)
		return (ft_free(s));
	ft_strncpy(new_s, s + line_len, n_len);
	new_s[n_len] = 0;
	free(s);
	return (new_s);
}
