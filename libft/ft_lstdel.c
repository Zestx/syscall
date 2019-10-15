/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:10:38 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/30 13:35:40 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *n_node;

	if (!alst || !*alst || !del)
		return ;
	while (*alst)
	{
		n_node = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = n_node;
	}
	*alst = NULL;
}
