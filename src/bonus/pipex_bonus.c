/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 23:59:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
