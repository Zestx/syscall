/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:08:18 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 14:06:12 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *schr;

	schr = (unsigned char*)s;
	while (n--)
	{
		if (*schr == (unsigned char)c)
			return (schr);
		schr++;
	}
	return (NULL);
}
