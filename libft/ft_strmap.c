/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:27:13 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 16:07:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
		smap[len] = f(s[len]);
		len++;
	}
	smap[len] = '\0';
	return (smap);
}
