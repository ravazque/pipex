/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:52:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/12 13:46:41 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(t_index *index, const char *argv[])
{
	if (index->route == NULL && (ft_strchr(index->cmd1, ' ') == 1
			|| ft_strchr(index->cmd2, ' ') == 1))
	{
		ft_putstr_fd("Error respecting the flag without the PATH.",
			STDERR_FILENO);
		freeindex(index);
		return (EXIT_FAILURE);
	}
	index->out = open(index->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (index->out < 0)
	{
		perror(index->outfile);
		return (-1);
	}
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
		return (close(index->out), freeindex(index), 2);
	index->in = open(index->infile, O_RDONLY);
	if (index->in < 0)
	{
		perror(index->infile);
		index->in = open("/dev/null", O_RDONLY);
		if (index->in < 0)
			return (freeindex(index), EXIT_FAILURE);
	}
	return (0);
}

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
		return (ft_clean_mem(&args), ft_putstr_fd("Error: invalid arguments\n",
				2), exit(127), (void)0);
	}
	while (args[++i])
		args[i] = ft_cleaner(args[i], "\"\'");
	path = find_executable(index, args[0]);
	if (!path)
	{
		return (ft_putstr_fd("Command not found: ", 2), ft_putstr_fd(args[0],
				2), ft_putchar_fd('\n', 2), freeindex(index),
			ft_clean_mem(&args), exit(127), (void)0);
	}
	execve(path, args, envp);
	perror("Exec failed");
	free(path);
	ft_clean_mem(&args);
	exit(EXIT_FAILURE);
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
