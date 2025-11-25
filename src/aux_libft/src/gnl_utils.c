/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 23:59:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = (char *)malloc(i + 2);
	else
		line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_buffer(char *buffer, ssize_t *flag)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (*flag = 0, NULL);
	}
	new_buffer = (char *)malloc(ft_strlen(buffer) - i);
	if (!new_buffer)
		return (free(buffer), *flag = 1, NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (*flag = 0, new_buffer);
}

static char	*init_buffer(char **buff)
{
	if (!*buff)
	{
		*buff = ft_strdup("");
		if (!*buff)
			return (NULL);
	}
	return (*buff);
}

static char	*read_loop(int fd, char **buff, char *tmp_buffer)
{
	char	*old_buff;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!ft_strchr(*buff, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, tmp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(tmp_buffer), free(*buff), *buff = NULL, NULL);
		tmp_buffer[bytes_read] = '\0';
		old_buff = *buff;
		*buff = ft_strjoin(*buff, tmp_buffer);
		free(old_buff);
		if (!*buff)
			return (free(tmp_buffer), NULL);
	}
	return (free(tmp_buffer), *buff);
}

char	*read_until_newline(int fd, char **buff)
{
	char	*tmp_buffer;

	if (!init_buffer(buff))
		return (NULL);
	tmp_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (free(*buff), *buff = NULL, NULL);
	return (read_loop(fd, buff, tmp_buffer));
}
