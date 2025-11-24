/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/23 00:00:00 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv)
{
	int	i;
	int	cmd_start;

	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->route = NULL;
	pipex->limiter = NULL;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		pipex->here_doc = 1;
		pipex->limiter = argv[2];
		pipex->cmd_count = argc - 4;
		cmd_start = 3;
	}
	else
	{
		pipex->here_doc = 0;
		pipex->cmd_count = argc - 3;
		cmd_start = 2;
	}
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

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->route)
	{
		while (pipex->route[i])
		{
			free(pipex->route[i]);
			i++;
		}
		free(pipex->route);
	}
	i = 0;
	if (pipex->cmds)
	{
		while (pipex->cmds[i])
		{
			free(pipex->cmds[i]);
			i++;
		}
		free(pipex->cmds);
	}
}

static char	*ft_cleaner_aux(char *str, char remover)
{
	char	*tmp;
	int		i;
	int		j;

	if (!str || !*str)
		return (NULL);
	tmp = (char *)malloc(ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != remover)
			tmp[j++] = str[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_cleaner(char *str, char *removers)
{
	int		i;
	char	*temp;

	if (!str || !*str)
		return (NULL);
	i = 0;
	while (removers[i] != '\0')
	{
		temp = ft_cleaner_aux(str, removers[i]);
		if (!temp)
			return (NULL);
		free(str);
		str = temp;
		i++;
	}
	return (str);
}

void	ft_clean_mem(char ***args)
{
	int	i;

	i = 0;
	if (args == NULL || *args == NULL)
		return ;
	while ((*args)[i] != NULL)
	{
		free((*args)[i]);
		(*args)[i] = NULL;
		i++;
	}
	free(*args);
	*args = NULL;
}
