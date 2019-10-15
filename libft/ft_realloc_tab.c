/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:41:31 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/09 20:41:10 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	get_size(char **tab)
{
	size_t	size;
	char	**ptr;

	ptr = tab;
	size = 0;
	while (*ptr)
	{
		size++;
		ptr++;
	}
	return (size + 2);
}

char			**ft_realloc_tab(char **old_tab, char *new_entry)
{
	char	**new_tab;
	char	**roam_o;
	char	**roam_n;

	if (!new_entry)
		return (NULL);
	if (!(new_tab = malloc(sizeof(new_tab) * get_size(old_tab))))
		exit(EXIT_FAILURE);
	roam_n = new_tab;
	roam_o = old_tab;
	while (*roam_o)
	{
		if (!(*roam_n = ft_strdup(*roam_o)))
			exit(EXIT_FAILURE);
		roam_o++;
		roam_n++;
	}
	if (!(*roam_n = ft_strdup(new_entry)))
		exit(EXIT_FAILURE);
	roam_n++;
	*roam_n = NULL;
	ft_free_tab2(old_tab);
	return (new_tab);
}
