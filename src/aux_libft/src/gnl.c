/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:34:42 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 15:48:43 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*extract_line(char *buffer)
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

static char	*update_buffer(char *buffer, ssize_t *flag)
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

static char	*read_until_newline(int fd, char **buff)
{
	char	*tmp_buffer;
	char	*old_buff;
	ssize_t	bytes_read;

	if (!*buff)
	{
		*buff = ft_strdup("");
		if (!*buff)
			return (NULL);
	}
	tmp_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (free(*buff), *buff = NULL, NULL);
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
	free(tmp_buffer);
	return (*buff);
}

static char	*g_buff[MAX_FD];

void	clear_gnl_buffer(int fd)
{
	if (fd >= 0 && fd < MAX_FD && g_buff[fd])
	{
		free(g_buff[fd]);
		g_buff[fd] = NULL;
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	ssize_t		flag;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (free(g_buff[fd]), g_buff[fd] = NULL, NULL);
	if (!read_until_newline(fd, &g_buff[fd]) || (g_buff[fd] && *g_buff[fd] == '\0'))
		return (free(g_buff[fd]), g_buff[fd] = NULL, NULL);
	line = extract_line(g_buff[fd]);
	if (!line)
		return (free(g_buff[fd]), g_buff[fd] = NULL, NULL);
	g_buff[fd] = update_buffer(g_buff[fd], &flag);
	if (!g_buff[fd] && flag == 1)
		return (free(line), NULL);
	return (line);
}
