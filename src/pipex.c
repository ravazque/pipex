/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:34:50 by ravazque          #+#    #+#             */
/*   Updated: 2025/09/08 00:48:39 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	execute_child1(t_index *index, int fd[2], char **envp)
{
	dup2(index->in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(index->in);
	exec_cmd(index, index->cmd1, envp);
}

static void	execute_child2(t_index *index, int fd[2], char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(index->out, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(index->out);
	exec_cmd(index, index->cmd2, envp);
}

static int	pipesandchild1(t_index *index, char **envp, int fd[2], pid_t *pid1)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	*pid1 = fork();
	if (*pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (*pid1 == 0)
		execute_child1(index, fd, envp);
	return (0);
}

static int	pipex(t_index *index, char **envp)
{
	int		fd[2];
	int		status1;
	int		status2;
	pid_t	pid1;
	pid_t	pid2;

	pipesandchild1(index, envp, fd, &pid1);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		execute_child2(index, fd, envp);
	close(fd[0]);
	close(fd[1]);
	close(index->in);
	close(index->out);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	freeindex(index);
	exit(WEXITSTATUS(status2));
}

int	main(int argc, char const *argv[], char **envp)
{
	t_index	index;
	int		aux;

	if (argc != 5)
	{
		ft_putstr_fd("\033[31mError: Invalid arguments\n\e[0m", 2);
		ft_putstr_fd("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n", 2);
		return (EXIT_FAILURE);
	}
	indexinit(&index, argv);
	setpath(&index, envp);
	aux = open_files(&index, argv);
	if (aux == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (aux == 2)
	{
		freeindex(&index);
		return (127);
	}
	pipex(&index, envp);
	return (0);
}
