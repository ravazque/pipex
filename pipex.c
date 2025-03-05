/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:34:50 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/04 20:27:06 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	pipex(t_index **index, char **envp);

int	main(int argc, char const *argv[], char **envp)
{
    t_index	index;

    if(argc != 5)
        ft_putstr_fd(ARGUMENTS, EXIT_FAILURE);
    index.infile = argv[1];
    index.outfile = argv[4];
    index.in = open(index.infile, O_RDONLY);
    if(index.in < 0)
        perror(index.infile);
    index.out = open(index.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(index.out < 0)
    {
		perror(index.outfile);
		// pipex(&index, envp);
		close(index.in);
		return (EXIT_FAILURE);
	}
    // index.exit = pipex(&index, envp);
	if (index.in > 0)
		close(index.in);
    if (index.out > 0)
        close(index.out);
	return (index.exit);
}

// =====================================

// int		in;
// int		out;
// const char	*infile;
// const char	*outfile;

// =====================================

