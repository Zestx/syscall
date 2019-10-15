/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:59:00 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 16:02:41 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		s_size;
	int		d_size;
	size_t	i;
	int		j;

	s_size = ft_strlen(src);
	d_size = ft_strlen(dst);
	i = 0;
	j = 0;
	if ((int)size <= d_size)
		return (s_size + size);
	while (dst[i] && i < size)
		i++;
	while (src[j] && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (d_size + s_size);
}
