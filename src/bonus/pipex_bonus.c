/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/29 17:43:30 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_putstr_fd("\033[31mError: Invalid arguments\n\e[0m", 2);
		ft_putstr_fd(PIPEX_B_ERR, 2);
		ft_putstr_fd(HD_ERR, 2);
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
