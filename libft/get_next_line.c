/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/09 20:41:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void		*ft_realloc(char *line, int old_size, int new_size)
{
	char *new_line;

	new_line = malloc(new_size + 1);
	if (!new_line)
		return (NULL);
	if (old_size)
	{
		ft_memcpy(new_line, line, old_size);
		free(line);
	}
	return (new_line);
}

static int		read_buffer(int fd, t_buffer *buff)
{
	int n;

	if ((buff->str < buff->end))
		return (1);
	n = read(fd, buff->rd, BUFF_SIZE);
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	buff->str = 0;
	buff->end = n;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_buffer	b[1000];
	t_util			u;

	u.p = NULL;
	u.curr_size = 0;
	if (fd < 0 || !line)
		return (-1);
	while (!u.p)
	{
		if ((u.n = read_buffer(fd, &b[fd])) <= 0)
			return (u.n ? u.n : u.curr_size != 0);
		if (!(u.p = ft_memchr(&b[fd].rd[b[fd].str], S, b[fd].end - b[fd].str)))
			u.size = b[fd].end - b[fd].str;
		else
			u.size = (u.p - b[fd].rd) - b[fd].str + 1;
		if (!(*line = ft_realloc(*line, u.curr_size, u.curr_size + u.size)))
			return (-1);
		ft_memcpy(*line + u.curr_size, &b[fd].rd[b[fd].str], u.size);
		*(*line + u.size) = '\0';
		u.curr_size += u.size;
		b[fd].str += u.size;
	}
	return (1);
}
