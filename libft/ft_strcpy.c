/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:21:40 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 15:14:20 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dst, const char *src)
{
	char *dstb;
	char *srcb;

	dstb = dst;
	srcb = (char*)src;
	while ((*dstb++ = *srcb++) != 0)
		;
	return (dst);
}
