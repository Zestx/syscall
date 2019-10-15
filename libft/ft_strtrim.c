/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:43:26 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 16:27:56 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspacex(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	int		start;
	size_t	len;
	int		i;

	start = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (ft_isspacex(s[start]))
		start++;
	while (s[start + len])
	{
		i = 0;
		while (ft_isspacex(s[start + len + i]))
		{
			if (!s[start + len + i + 1])
				return (ft_strsub(s, start, len));
			i++;
		}
		len++;
	}
	return (ft_strsub(s, start, len));
}
