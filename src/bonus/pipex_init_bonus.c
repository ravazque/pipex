/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/29 17:42:52 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static int	init_pipex_hd(t_pipex *pipex, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		pipex->here_doc = 1;
		pipex->limiter = argv[2];
		pipex->cmd_count = argc - 4;
		if (argc != 6)
		{
			ft_putstr_fd("\033[31mError: Invalid arguments\n\e[0m", 2);
			ft_putstr_fd(PIPEX_B_ERR, 2);
			ft_putstr_fd(HD_ERR, 2);
			exit (EXIT_FAILURE);
		}
		return (3);
	}
	else
	{
		pipex->here_doc = 0;
		pipex->cmd_count = argc - 3;
		return (2);
	}
}

void	init_pipex(t_pipex *pipex, int argc, char **argv)
{
	int	i;
	int	cmd_start;

	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->route = NULL;
	pipex->limiter = NULL;
	cmd_start = init_pipex_hd(pipex, argc, argv);
	pipex->cmds = (char **)malloc(sizeof(char *) * (pipex->cmd_count + 1));
	if (!pipex->cmds)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i] = ft_strdup(argv[cmd_start + i]);
		i++;
	}
	pipex->cmds[i] = NULL;
}

// If heredoc is being used, pipex can only be used as a single pipe mode.