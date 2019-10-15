/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:08:01 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 15:18:50 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*buffer;
	size_t	length;

	length = 0;
	while (s1[length])
		length++;
	buffer = (char*)malloc((sizeof(char) * length) + 1);
	if (!buffer)
		return (NULL);
	ft_memcpy(buffer, s1, length);
	*(buffer + length) = '\0';
	return (buffer);
}
