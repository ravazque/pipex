/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 23:46:53 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	setpath(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	pipex->route = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			pipex->route = ft_split(envp[i] + 5, ':');
			if (!pipex->route)
			{
				ft_putstr_fd("Error al dividir el PATH.\n", 2);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		i++;
	}
}

char	*find_executable(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (pipex->route && pipex->route[i])
	{
		tmp = ft_strjoin(pipex->route[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	exec_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	char	**args;
	char	*path;
	int		i;

	i = -1;
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		ft_putstr_fd("Error: invalid arguments\n", 2);
		ft_clean_mem(&args);
		free_pipex(pipex);
		exit(127);
	}
	while (args[++i])
		args[i] = ft_cleaner(args[i], "\"\'");
	path = find_executable(pipex, args[0]);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putchar_fd('\n', 2);
		free_pipex(pipex);
		ft_clean_mem(&args);
		exit(127);
	}
	execve(path, args, envp);
	perror("Exec failed");
	free(path);
	ft_clean_mem(&args);
	exit(EXIT_FAILURE);
}

void	open_files(t_pipex *pipex, char **argv, int argc)
{
	if (pipex->here_doc)
	{
		pipex->outfile = open(argv[argc - 1], 01 | 0100 | 02000, 0644);
		if (pipex->outfile < 0)
		{
			perror(argv[argc - 1]);
			pipex->outfile = open("/dev/null", O_WRONLY);
		}
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
		{
			perror(argv[1]);
			pipex->infile = open("/dev/null", O_RDONLY);
		}
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (pipex->outfile < 0)
		{
			perror(argv[argc - 1]);
			pipex->outfile = open("/dev/null", O_WRONLY);
		}
	}
}

void	handle_here_doc(t_pipex *pipex)
{
	char	*line;
	int		fd[2];
	size_t	limiter_len;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	limiter_len = ft_strlen(pipex->limiter);
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strlen(line) >= limiter_len
			&& ft_strncmp(line, pipex->limiter, limiter_len) == 0
			&& (line[limiter_len] == '\n' || line[limiter_len] == '\0'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
	}
	clear_gnl_buffer(STDIN_FILENO);
	close(fd[1]);
	pipex->infile = fd[0];
}
