/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:37:28 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/29 19:07:08 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*procd_list;

	procd_list = malloc(sizeof(t_list*));
	if (!procd_list)
		return (NULL);
	if (!lst || !f)
	{
		free(procd_list);
		return (NULL);
	}
	procd_list = f(lst);
	procd_list->next = ft_lstmap(lst->next, f);
	return (procd_list);
}
