/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:34:42 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/25 02:57:39 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*get_next_line(int fd, char **static_buffer)
{
	char		*line;
	ssize_t		flag;

	if (fd < 0 || BUFFER_SIZE <= 0 || !static_buffer)
		return (free(*static_buffer), *static_buffer = NULL, NULL);
	if (!read_until_newline(fd, static_buffer) || (*static_buffer
			&& **static_buffer == '\0'))
		return (free(*static_buffer), *static_buffer = NULL, NULL);
	line = extract_line(*static_buffer);
	if (!line)
		return (free(*static_buffer), *static_buffer = NULL, NULL);
	*static_buffer = update_buffer(*static_buffer, &flag);
	if (!*static_buffer && flag == 1)
		return (free(line), NULL);
	return (line);
}
