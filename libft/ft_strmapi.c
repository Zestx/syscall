/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:32:32 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 16:08:43 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*smap;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	smap = (char*)malloc(sizeof(char) * (len + 1));
	if (!smap)
		return (NULL);
	len = 0;
	while (s[len])
	{
		smap[len] = f(len, s[len]);
		len++;
	}
	smap[len] = '\0';
	return (smap);
}
