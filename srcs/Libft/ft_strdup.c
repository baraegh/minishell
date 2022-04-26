/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:16:50 by eel-ghan          #+#    #+#             */
/*   Updated: 2021/11/14 12:45:10 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (*src)
	{
		*(dest + i) = *src;
		src++;
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*p;

	p = (char *) malloc(ft_strlen(s1) + 1);
	if (!p)
		return (0);
	ft_strcpy(p, s1);
	return (p);
}
