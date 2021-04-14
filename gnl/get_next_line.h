/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifontai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 00:28:44 by vifontai          #+#    #+#             */
/*   Updated: 2020/01/24 01:16:53 by vifontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# define FD 4096
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

int		get_next_line(const int fd, char **line);
char	*ft_strnew_gnl(size_t size);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
void	*ft_memset_gnl(void *s, int c, size_t n);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strsub_gnl(char const *s, unsigned int start, size_t len);
char	*ft_strdup_gnl(const char *s);
void	ft_strdel_gnl(char **as);

#endif
