/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:05:41 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/11 21:29:34 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(t_index *index, char **envp)
{
	int		fd[2];
	int		status1;
	int		status2;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		execute_child1(index, fd, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		execute_child2(index, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (status1 != 0 && status2 == 0 && !index->cmd1[1])
	{
		return (WEXITSTATUS(status1));
	}
	return (WEXITSTATUS(status2));
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

void ft_clean_mem(char ***args)
{
    int i = 0;

    if (args == NULL || *args == NULL)
        return;
    while ((*args)[i] != NULL)
	{
        free((*args)[i]);
        (*args)[i] = NULL;
        i++;
    }
    free(*args);
    *args = NULL;
}
