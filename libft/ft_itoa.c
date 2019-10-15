/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 15:11:43 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 13:24:56 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int count;

	count = 1;
	while (n /= 10)
		count++;
	return (count);
}

static int	isnegative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char		*ft_itoa(int n)
{
	char	*number;
	int		len;
	int		neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if ((neg = isnegative(n)) == 1)
		n *= -1;
	len = count_digits(n) + 1 + neg;
	number = (char*)malloc(sizeof(char) * len);
	if (!number)
		return (NULL);
	number[--len] = '\0';
	while (len--)
	{
		number[len] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		*number = '-';
	return (number);
}
