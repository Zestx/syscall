/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:45:50 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 12:23:16 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstcount(t_list *lst)
{
	int		count;
	t_list	*p_node;

	if (!lst)
		return (0);
	p_node = lst;
	count = 0;
	while (p_node)
	{
		count++;
		if (!(p_node = p_node->next))
			break ;
	}
	return (count);
}
