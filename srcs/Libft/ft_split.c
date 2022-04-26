/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:45:52 by eel-ghan          #+#    #+#             */
/*   Updated: 2021/11/16 20:42:49 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_tab(char const *s, char c)
{
	int	count_tabs;
	int	i;

	count_tabs = 0;
	i = 0;
	while (*(s + i) == c)
		i++;
	while (*(s + i))
	{
		if (*(s + i) == c)
		{
			count_tabs++;
			while (*(s + i) == c)
				i++;
			continue ;
		}
		i++;
	}
	if (*(s + i - 1) != c)
		count_tabs++;
	return (count_tabs);
}

static void	ft_get_next_tab(char **s, int *len, char c)
{
	int	i;

	*s += *len;
	*len = 0;
	i = 0;
	while (**s && **s == c)
		(*s)++;
	while ((*s)[i])
	{
		if ((*s)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

char	**ft_freetab(char **ptr, int i)
{
	while (i >= 0)
		free(ptr[i--]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*str;
	int		i;
	int		len;

	if (!s)
		return (0);
	if (*s == '\0')
		return ((char **)ft_calloc(2, sizeof(char *)));
	ptr = (char **) malloc((ft_count_tab(s, c) + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	i = 0;
	str = (char *)s;
	len = 0;
	while (i < ft_count_tab(s, c))
	{
		ft_get_next_tab(&str, &len, c);
		ptr[i] = (char *) malloc((len + 1) * sizeof(char));
		if (!ptr[i])
			return (ft_freetab(ptr, i));
		ft_strlcpy(ptr[i++], str, len + 1);
	}
	ptr[i] = 0;
	return (ptr);
}
