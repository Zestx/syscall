/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:39:21 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 16:27:03 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ssub;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	ssub = (char*)malloc(len + 1);
	if (!ssub)
		return (NULL);
	i = 0;
	while (start--)
		i++;
	j = 0;
	while (len--)
	{
		ssub[j] = s[i];
		i++;
		j++;
	}
	ssub[j] = '\0';
	return (ssub);
}
