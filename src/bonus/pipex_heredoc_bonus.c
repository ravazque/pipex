/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 23:59:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	is_limiter(char *line, char *limiter, size_t limiter_len)
{
	if (ft_strlen(line) >= limiter_len
		&& ft_strncmp(line, limiter, limiter_len) == 0
		&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		return (1);
	return (0);
}

static void	read_here_doc_lines(t_pipex *pipex, int write_fd)
{
	char	*line;
	char	*buffer;
	size_t	limiter_len;

	buffer = NULL;
	limiter_len = ft_strlen(pipex->limiter);
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(STDIN_FILENO, &buffer);
	while (line)
	{
		if (is_limiter(line, pipex->limiter, limiter_len))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, write_fd);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN_FILENO, &buffer);
	}
	if (buffer)
		free(buffer);
}

void	handle_here_doc(t_pipex *pipex)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	read_here_doc_lines(pipex, fd[1]);
	close(fd[1]);
	pipex->infile = fd[0];
}
