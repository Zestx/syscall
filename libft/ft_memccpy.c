/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:38:32 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 14:04:43 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;

	d = (unsigned char*)dst;
	while (n--)
		if ((unsigned char)c == (*d++ = *(unsigned char*)src++))
			return ((void*)d);
	return (NULL);
}
