/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:21:47 by eel-ghan          #+#    #+#             */
/*   Updated: 2021/11/17 12:59:30 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_sub(char *tab, char const *s, unsigned int start, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		*(tab + i) = (char)s[start];
		start++;
		i++;
	}
	*(tab + i) = '\0';
	return (tab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tab;
	size_t			size;

	if (!s)
		return (0);
	size = ft_strlen(s);
	if (start > size || len == 0)
		return (ft_strdup(""));
	if (start + len < size)
	{
		tab = (char *) malloc((len + 1) * sizeof(char));
		size = len;
	}
	else
	{
		tab = (char *) malloc((size - start + 1) * sizeof(char));
		size -= start;
	}
	if (!tab)
		return (0);
	return (ft_sub(tab, s, start, size));
}
