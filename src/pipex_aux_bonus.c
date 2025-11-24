/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by ravazque          #+#    #+#             */
/*   Updated: 2025/11/24 23:45:31 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
