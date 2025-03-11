/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:44:03 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/10 18:34:26 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# define ARGUMENTS "Error: Número incorrecto de argumentos\n"

typedef struct s_index
{
	int			exit;
	int			in;
	int			out;
	const char	*infile;
	const char	*outfile;
	char		**route;
	char		*cmd1;
	char		*cmd2;
}				t_index;

void			indexinit(t_index *index, const char *argv[]);
void			freeindex(t_index *index);
void			setpath(t_index *index, char **envp);
char			*find_executable(t_index *index, char *cmd);
void			exec_cmd(t_index *index, char *cmd, char **envp);
int				pipex(t_index *index, char **envp);

#endif
