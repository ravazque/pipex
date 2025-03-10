/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:52:11 by ravazque          #+#    #+#             */
/*   Updated: 2025/03/10 15:25:21 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void indexinit(t_index *index, char *argv[])
{
    index->in = -1;
    index->out = -1;
    index->i = 0;
    index->infile = argv[1];
    index->outfile = argv[4];
    index->route = NULL;
    index->exit = EXIT_FAILURE;
}

void setpath(t_index *index, char **envp)
{
    int i;

    i = 0;
    while(envp[i] != NULL)
    {
        if(ft_strncmp(PATH, envp[i], 5) == 0)
        {
            index->route = ft_split(envp[i] + 5, ':');
            if (index->route == NULL)
            {
                ft_putstr_fd("Error al dividir el PATH.\n", 2);
                exit(EXIT_FAILURE);
            }
            break;
        }
        i++;
    }
}

void freeindex(t_index *index)
{
    int i;
    
    if (index->route != NULL)
    {
        i = 0;
        while(index->route[i])
        {
            free((void *)index->route[i]);
            i++;
        }
        free((void *)index->route);
    }
}
