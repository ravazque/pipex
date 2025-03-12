/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:52:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/11 21:24:34 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_executable(t_index *index, char *cmd)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (index->route && index->route[i])
	{
		tmp = ft_strjoin(index->route[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	exec_cmd(t_index *index, char *cmd, char **envp)
{
	char	**args;
	char	*path;
	int		i;

	i = -1;
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		ft_clean_mem(&args);
		ft_putstr_fd("Error: invalid arguments\n", 2);
		exit(127);
	}
	while (args[++i])
		args[i] = ft_cleaner(args[i], "\"\'");
	path = find_executable(index, args[0]);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putchar_fd('\n', 2);
		exit(127);
	}
	execve(path, args, envp);
	perror("Exec failed");
	free(path);
	ft_clean_mem(&args);
	exit(EXIT_FAILURE);
}

void	indexinit(t_index *index, const char *argv[])
{
	index->in = -1;
	index->out = -1;
	index->infile = argv[1];
	index->outfile = argv[4];
	index->route = NULL;
	index->cmd1 = ft_strdup(argv[2]);
	index->cmd2 = ft_strdup(argv[3]);
	index->exit = EXIT_FAILURE;
}

void	setpath(t_index *index, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			index->route = ft_split(envp[i] + 5, ':');
			if (!index->route)
			{
				ft_putstr_fd("Error al dividir el PATH.\n", 2);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		i++;
	}
}

void	freeindex(t_index *index)
{
	int	i;

	i = 0;
	if (index->route)
	{
		while (index->route[i])
		{
			free((void *)index->route[i]);
			i++;
		}
		free((void *)index->route);
	}
	if (index->cmd1)
		free(index->cmd1);
	if (index->cmd2)
		free(index->cmd2);
}
