/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:44:03 by ravazque          #+#    #+#             */
/*   Updated: 2025/09/08 00:47:57 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/libft/libft.h"

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
char			*ft_cleaner(char *str, char *removers);
void			ft_clean_mem(char ***args);
void			setpath(t_index *index, char **envp);
void			exec_cmd(t_index *index, char *cmd, char **envp);
char			*find_executable(t_index *index, char *cmd);
int				open_files(t_index *index, const char *argv[]);
#endif
