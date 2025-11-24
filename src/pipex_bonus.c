/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/23 00:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	execute_cmd_child(t_pipex *pipex, char **envp, int i, int pipefd[2])
{
	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
	}
	else if (i > 0 && pipex->infile > 0 && !pipex->here_doc)
		close(pipex->infile);
	if (i == pipex->cmd_count - 1)
	{
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		if (pipex->outfile > 0)
			close(pipex->outfile);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	exec_cmd(pipex, pipex->cmds[i], envp);
}

void	execute_pipeline(t_pipex *pipex, char **envp)
{
	int		pipefd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;
	int		status;
	int		exit_status;

	i = 0;
	prev_fd = -1;
	exit_status = 0;
	while (i < pipex->cmd_count)
	{
		if (i < pipex->cmd_count - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			execute_cmd_child(pipex, envp, i, pipefd);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < pipex->cmd_count - 1)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		i++;
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		wait(&status);
		exit_status = WEXITSTATUS(status);
		i++;
	}
	(void)exit_status;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_putstr_fd("\033[31mError: Invalid arguments\n\e[0m", 2);
		ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> ... <file2>\n", 2);
		ft_putstr_fd("       ./pipex here_doc <LIMITER> <cmd> ... <file>\n",
			2);
		return (EXIT_FAILURE);
	}
	init_pipex(&pipex, argc, argv);
	setpath(&pipex, envp);
	open_files(&pipex, argv, argc);
	if (pipex.here_doc)
		handle_here_doc(&pipex);
	execute_pipeline(&pipex, envp);
	if (pipex.infile > 0)
		close(pipex.infile);
	if (pipex.outfile > 0)
		close(pipex.outfile);
	free_pipex(&pipex);
	return (0);
}
