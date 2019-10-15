/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:46:20 by qbackaer          #+#    #+#             */
/*   Updated: 2018/10/25 18:16:10 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static int	count_words(char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_fill_array(char **w_array, char *s, int idx, char c)
{
	int size;
	int i;

	size = 0;
	while (*s == c)
		s++;
	while ((s[size] != c) && s[size] != '\0')
		size++;
	w_array[idx] = malloc(sizeof(*s) * (size + 1));
	i = 0;
	if (!w_array[idx])
	{
		while (i++ < idx)
			free(w_array[idx]);
		free(w_array);
		return (NULL);
	}
	while (i < size)
	{
		w_array[idx][i] = s[i];
		i++;
	}
	w_array[idx][i] = '\0';
	return (s + size);
}

char		**ft_strsplit(char const *s, char c)
{
	int		wc;
	int		i;
	char	**w_array;

	if (!s)
		return (NULL);
	wc = count_words((char*)s, c);
	w_array = (char**)malloc(sizeof(w_array) * (wc + 1));
	if (!w_array)
		return (NULL);
	w_array[wc] = NULL;
	i = 0;
	while (i < wc)
	{
		s = ft_fill_array(w_array, (char*)s, i, c);
		i++;
	}
	return (w_array);
}
