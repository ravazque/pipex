/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:05:41 by ravazque          #+#    #+#             */
/*   Updated: 2025/09/08 00:48:27 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
