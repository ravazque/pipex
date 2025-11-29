/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/29 17:43:11 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../src/aux_libft/include/libft.h"

# define PIPEX_B_ERR "Usage: ./pipex_bonus <file1> <cmd1> <cmd2> ... <file2>\n"
# define HD_ERR "       ./pipex_bonus here_doc <LIMITER> <cmd1> <cmd2> <file> \
[ << x | x >> outfile ]\n"

typedef struct s_pipex
{
	int			here_doc;
	int			infile;
	int			outfile;
	int			cmd_count;
	char		**cmds;
	char		**route;
	char		*limiter;
	int			i;
}				t_pipex;

void			init_pipex(t_pipex *pipex, int argc, char **argv);
void			free_pipex(t_pipex *pipex);
void			setpath(t_pipex *pipex, char **envp);
void			exec_cmd(t_pipex *pipex, char *cmd, char **envp);
char			*find_executable(t_pipex *pipex, char *cmd);
char			*ft_cleaner(char *str, char *removers);
void			ft_clean_mem(char ***args);
void			handle_here_doc(t_pipex *pipex);
void			open_files(t_pipex *pipex, char **argv, int argc);
void			execute_pipeline(t_pipex *pipex, char **envp);

#endif
