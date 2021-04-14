/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifontai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 00:28:39 by vifontai          #+#    #+#             */
/*   Updated: 2020/01/24 01:18:23 by vifontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == '\0' && !c)
		return ((char *)s + i);
	return (NULL);
}

void	ft_strdel_gnl(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}

void	*ft_memset_gnl(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)s;
	while (i < n)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		j++;
	while (s2[i])
		i++;
	if (!(res = (char *)malloc(sizeof(char) * (j + i + 1))))
		return (NULL);
	j = 0;
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strdup_gnl(const char *s)
{
	char	*dest;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (!(dest = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
