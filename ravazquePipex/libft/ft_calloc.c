/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:59:02 by ravazque          #+#    #+#             */
/*   Updated: 2024/10/03 15:03:52 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tsize;
	void	*ptr;
	char	*init_ptr;
	size_t	i;

	tsize = nmemb * size;
	ptr = malloc(tsize);
	if (!ptr)
	{
		return (NULL);
	}
	init_ptr = (char *)ptr;
	i = 0;
	while (i < tsize)
	{
		init_ptr[i] = 0;
		i++;
	}
	return (ptr);
}
