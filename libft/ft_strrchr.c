/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:59:54 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/25 18:15:39 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*match;

	match = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			match = (char*)(s + i);
		i++;
	}
	if (!c)
		return ((char*)(s + i));
	if (match == 0)
		return (NULL);
	return (match);
}
