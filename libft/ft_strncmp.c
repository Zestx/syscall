/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:11:29 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 16:12:52 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char *sb1;
	char *sb2;

	sb1 = (char*)s1;
	sb2 = (char*)s2;
	if (!s1 && !s2)
		return (0);
	if (n)
		while ((*sb1 || *sb2) && n)
		{
			if (*sb1 != *sb2)
				return ((unsigned char)*sb1 - (unsigned char)*sb2);
			sb1++;
			sb2++;
			n--;
		}
	return (0);
}
