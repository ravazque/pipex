/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipeline_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 23:59:59 by ravazque         ###   ########.fr       */
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

static void	create_process(t_pipex *pipex, char **envp,
		int *pipefd, int prev_fd)
{
	pid_t	pid;

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
		execute_cmd_child(pipex, envp, pipex->i, pipefd);
	}
}

static int	wait_all_processes(t_pipex *pipex)
{
	int	status;
	int	exit_status;
	int	j;

	exit_status = 0;
	j = 0;
	while (j < pipex->cmd_count)
	{
		wait(&status);
		exit_status = WEXITSTATUS(status);
		j++;
	}
	return (exit_status);
}

void	execute_pipeline(t_pipex *pipex, char **envp)
{
	int		pipefd[2];
	int		prev_fd;

	pipex->i = 0;
	prev_fd = -1;
	while (pipex->i < pipex->cmd_count)
	{
		if (pipex->i < pipex->cmd_count - 1 && pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		create_process(pipex, envp, pipefd, prev_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (pipex->i < pipex->cmd_count - 1)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		pipex->i++;
	}
	(void)wait_all_processes(pipex);
}
