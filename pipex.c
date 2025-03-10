/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:34:50 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/10 16:06:29 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	pipex(t_index **index, char **envp);

int	main(int argc, char const *argv[], char **envp)
{
    t_index	index;

    if(argc != 5)
        return(ft_putstr_fd(ARGUMENTS, EXIT_FAILURE), EXIT_FAILURE);
    indexinit(&index, argv);
    setpath(&index, envp);
    index.in = open(index.infile, O_RDONLY, 0644);
    if(index.in < 0)
    {
        perror(index.infile);
        freeindex(&index);
        return(EXIT_FAILURE);
    }
    index.out = open(index.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(index.out < 0)
    {
		perror(index.outfile);
		// pipex(&index, envp);
		close(index.in);
        freeindex(&index);
		return (EXIT_FAILURE);
	}
    // index.exit = pipex(&index, envp);
	if (index.in > 0)
		close(index.in);
    if (index.out > 0)
        close(index.out);
    freeindex(&index);
	return (index.exit);
}

// ==================================

// int          in
// int          in
// const char   *infile
// const char   *outfile

// ==================================

