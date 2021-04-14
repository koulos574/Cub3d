/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifontai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 00:28:31 by vifontai          #+#    #+#             */
/*   Updated: 2020/01/24 01:17:40 by vifontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strsub_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len > 0 && s[start])
	{
		str[i++] = s[start++];
		len--;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strnew_gnl(size_t size)
{
	char *s;

	if (!(s = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_memset_gnl(s, 0, sizeof(char) * size + 1);
	return (s);
}

int		find(char *str)
{
	int		a;

	a = 0;
	while ((str[a] != '\0') && (str[a] != '\n'))
		a++;
	return (a);
}

int		go_read(char **str, const int fd, char **line)
{
	char	*tmp;
	int		z;

	z = find(str[fd]);
	if (ft_strchr_gnl(str[fd], '\n'))
	{
		*line = ft_strsub_gnl(str[fd], 0, z);
		tmp = ft_strdup_gnl(str[fd] + z + 1);
		ft_strdel_gnl(&str[fd]);
		str[fd] = ft_strdup_gnl(tmp);
		free(tmp);
	}
	else if (ft_strchr_gnl(str[fd], '\0'))
	{
		*line = ft_strdup_gnl(str[fd]);
		ft_strdel_gnl(&str[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*str[FD];
	char			*tmp;
	char			buff[BUFFER_SIZE + 1];
	int				ret;

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strnew_gnl(1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = ft_strjoin_gnl(str[fd], buff);
		free(str[fd]);
		str[fd] = tmp;
		if (ft_strchr_gnl(str[fd], '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	if (ret == 0 && (str[fd][0] == '\0' || str[fd] == NULL))
		return (0);
	return (go_read(str, fd, line));
}
