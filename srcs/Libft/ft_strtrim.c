/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barae <barae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:02:03 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/04/26 00:30:24 by barae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isequal(char s, const char *set)
{
	while (*set)
	{
		if (s == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_count_left(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!ft_isequal(s1[i], set))
			break ;
		i++;
	}
	return (i);
}

static int	ft_count_right(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (!ft_isequal(s1[i], set))
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	int	i;
	int	j;
	int	x;

	if (!s1 || !set)
		return (0);
	i = ft_count_left(s1, set);
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	j = ft_count_right(s1, set);
	str = (char *) malloc((j - i + 2) * sizeof(char));
	if (!str)
		return (0);
	x = 0;
	while (i <= j)
	{
		str[x] = s1[i];
		x++;
		i++;
	}
	str[x] = '\0';
	return (str);
}
