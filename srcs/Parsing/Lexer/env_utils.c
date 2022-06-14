/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:38:21 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/12 21:23:49 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	free_str(char **str)
{
	free(str[0]);
	free(str[1]);
	free(str);
}

char	*get_value(char *s1, char *s2, char **str)
{
	char	*value;

	if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
	{
		value = ft_strdup(str[1]);
		free_str(str);
		return (value);
	}
	return (NULL);
}

char	*get_env_value(char **str, char *s)
{
	char	*value;

	if (ft_strlen(str[0]) >= ft_strlen(s))
	{
		value = get_value(s, str[0], str);
		if (value != NULL)
			return (value);
	}
	else
	{
		value = get_value(str[0], s, str);
		if (value != NULL)
			return (value);
	}
	return (value);
}

char	*get_env(t_vr *vr, char *s)
{
	int		i;
	char	**str;
	char	*value;

	i = 0;
	while (i < vr->envlen)
	{
		str = ft_split(vr->env[i], '=');
		if (!str)
			return (NULL);
		value = get_env_value(str, s);
		if (value != NULL)
			return (value);
		free_str(str);
		i++;
	}
	return (NULL);
}
