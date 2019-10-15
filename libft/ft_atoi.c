/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 14:54:40 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/05 16:58:53 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspacex(char c)
{
	if (c == ' ')
		return (1);
	else if (c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	long			nb;
	int				neg;
	char			*strb;

	strb = (char*)str;
	nb = 0;
	neg = 0;
	while (ft_isspacex(*strb))
		strb++;
	if (*strb == '-')
		neg = 1;
	if (*strb == '-' || *strb == '+')
		strb++;
	while (*strb >= '0' && *strb <= '9')
	{
		nb = (nb * 10) + (*strb - '0');
		strb++;
	}
	if (nb < 0 && !neg)
		return (-1);
	else if (nb < 0)
		return (0);
	if (neg)
		return ((int)-nb);
	return ((int)nb);
}
