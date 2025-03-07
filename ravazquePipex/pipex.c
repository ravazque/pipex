/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:34:50 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/07 17:42:42 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	pipex(t_index **index, char **envp);

int	main(int argc, char const *argv[], char **envp)
{
	t_index	index;

	if (argc != 5)
		return (ft_putstr_fd(ARGUMENTS, 2), EXIT_FAILURE);
	indexinit(&index, argv);
	setpath(&index, envp);
	index.in = open(index.infile, O_RDONLY);
	if (index.in < 0)
		return (perror(index.infile), free_index(&index), EXIT_FAILURE);
	index.out = open(index.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (index.out < 0)
	{
		perror(index.outfile);
		// pipex(&index, envp);
		close(index.in);
		free_index(&index);
		return (EXIT_FAILURE);
	}
	// index.exit = pipex(&index, envp);
	if (index.in > 0)
		close(index.in);
	if (index.out > 0)
		close(index.out);
	free_index(&index);
	return (index.exit);
}

// =====================================

// int		in;
// int		out;
// const char	*infile;
// const char	*outfile;

// =====================================
