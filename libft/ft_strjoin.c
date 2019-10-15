/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:22:17 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 16:02:48 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	sjoin = (char*)malloc(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1);
	if (!sjoin)
		return (NULL);
	while (s1[i])
	{
		sjoin[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		sjoin[i + j] = s2[j];
		j++;
	}
	sjoin[i + j] = '\0';
	return (sjoin);
}
