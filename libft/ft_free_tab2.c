/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:42:41 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/06 23:20:47 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_free_tab2(char **tab)
{
	char	**roam;

	if (!tab)
		return ;
	roam = tab;
	while (*roam)
	{
		free(*roam);
		roam++;
	}
	free(tab);
}
