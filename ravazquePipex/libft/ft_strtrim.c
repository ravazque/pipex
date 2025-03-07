/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravazque <ravazque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:41:22 by ravazque          #+#    #+#             */
/*   Updated: 2024/10/04 09:36:36 by ravazque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ischar(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ret;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ischar(s1[start], set))
		start++;
	while (end > start && ischar(s1[end], set))
		end--;
	ret = (char *)malloc((end - start + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &s1[start], end - start + 2);
	return (ret);
}
