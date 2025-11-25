/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 23:59:59 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	**prepare_args(char *cmd, t_pipex *pipex)
{
	char	**args;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		ft_putstr_fd("Error: invalid arguments\n", 2);
		ft_clean_mem(&args);
		free_pipex(pipex);
		exit(127);
	}
	i = -1;
	while (args[++i])
		args[i] = ft_cleaner(args[i], "\"\'");
	return (args);
}

static void	handle_cmd_not_found(t_pipex *pipex, char **args)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putchar_fd('\n', 2);
	free_pipex(pipex);
	ft_clean_mem(&args);
	exit(127);
}

void	exec_cmd(t_pipex *pipex, char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = prepare_args(cmd, pipex);
	path = find_executable(pipex, args[0]);
	if (!path)
		handle_cmd_not_found(pipex, args);
	execve(path, args, envp);
	perror("Exec failed");
	free(path);
	ft_clean_mem(&args);
	exit(EXIT_FAILURE);
}
