/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:44:03 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/04 18:44:15 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# define FILE "bash: no such file or directory: "
# define COMMAND "bash: command not found: "
# define ARGUMENTS "Error: bad number of arguments\n"
# define CHILD "child error"
# define PIPE "pipe error"
# define PATH "PATH="
# define HERE_DOC "here_doc"
# define TMP_FILE "/tmp/pipex_tmp"

typedef struct s_index
{
	int		i;
	int		exit;
	int		in;
	int		out;
	const char	*infile;
	const char	*outfile;
}	t_index;

#endif
