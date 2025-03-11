/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:34:50 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/10 18:48:48 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child1(t_index *index, int fd[2], char **envp)
{
	dup2(index->in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(index->in);
	exec_cmd(index, index->cmd1, envp);
}

void	execute_child2(t_index *index, int fd[2], char **envp)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(index->out, STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(index->out);
	exec_cmd(index, index->cmd2, envp);
}

int	pipex(t_index *index, char **envp)                              // arreglar la longitud de la función
{
	int		fd[2];
	int		status1;
	int		status2;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		execute_child1(index, fd, envp);
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
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2));
}

int	open_files(t_index *index)
{
    index->out = open(index->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (index->out < 0)
    {
        perror(index->outfile);
        freeindex(index);
        return (EXIT_FAILURE);
    }
	index->in = open(index->infile, O_RDONLY);
	if (index->in < 0)
	{
		perror(index->infile);
        close(index->out);
		freeindex(index);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char const *argv[], char **envp)
{
	t_index	index;

	if (argc != 5)
		return (ft_putstr_fd(ARGUMENTS, 2), EXIT_FAILURE);
	indexinit(&index, argv);
	setpath(&index, envp);
	if (open_files(&index) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	index.exit = pipex(&index, envp);
	if (index.in > 0)
		close(index.in);
	if (index.out > 0)
		close(index.out);
    
	freeindex(&index);
	return (index.exit);
}
