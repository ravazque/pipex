/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:20:43 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/07 17:45:42 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setpath(t_index *index, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(PATH, envp[i], 5) == 0)
		{
			index->route = ft_split(envp[i] + 5, ':');
			if (index->route == NULL)
			{
				ft_putstr_fd("Error al dividir PATH.\n", 2);
				exit(EXIT_FAILURE);
			}
			break ;
		}
		i++;
	}
}

void	indexinit(t_index *index, const char *argv[])
{
	index->infile = argv[1];
	index->outfile = argv[4];
	index->in = -1;
	index->out = -1;
	index->route = NULL;
	index->exit = EXIT_FAILURE;
}

void	free_index(t_index *index)
{
	int	i;

	if (index->route != NULL)
	{
		i = 0;
		while (index->route[i] != NULL)
		{
			free((void *)index->route[i]);
			i++;
		}
		free((void *)index->route);
	}
}
