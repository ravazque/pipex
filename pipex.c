/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:34:50 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/11 20:57:46 by ravazque         ###   ########.fr       */
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

int	open_files(t_index *index, const char *argv[])
{
	if (index->route == NULL && (ft_strchr(index->cmd1, ' ') == 1 || ft_strchr(index->cmd2, ' ') == 1))
	{
		ft_putstr_fd("Error respecting the flag without the PATH.", STDERR_FILENO);
		freeindex(index);
		return (EXIT_FAILURE);
	}
	index->out = open(index->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (index->out < 0)
	{
		perror(index->outfile);
		freeindex(index);
		return (EXIT_FAILURE);
	}
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		close(index->out);
		freeindex(index);
		return (2);
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
	int 	aux;

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
		return(0);
	index.exit = pipex(&index, envp);
	if (index.in > 0)
		close(index.in);
	if (index.out > 0)
		close(index.out);	
	freeindex(&index);
	return (index.exit);
}
