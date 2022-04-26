/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:08:40 by eel-ghan          #+#    #+#             */
/*   Updated: 2021/11/03 16:29:20 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len >= dstsize || dstsize == 0)
		return (dstsize + src_len);
	i = dest_len;
	while (*src && i < dstsize - 1)
	{
		*(dst + i) = *src;
		src++;
		i++;
	}
	*(dst + i) = '\0';
	return (dest_len + src_len);
}
