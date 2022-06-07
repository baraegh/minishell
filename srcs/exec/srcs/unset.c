/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:05:54 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/07 17:48:15 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	ft_freetwo(char **target)
{
	int	i;

	i = 0;
	while (target[i])
	{
		free(target[i]);
		i++;
	}
	free(target);
	target = NULL;
}

char	**unset_ut(char *arg, char **target, int len)
{
	char	**str;
	char	*word;
	int		i;
	int		j;

	i = 0;
	while (target[i++])
		;
	str = malloc(sizeof(char *) * i);
	if (!str)
		ft_error("allocation failde", 1);
	i = -1;
	j = -1;
	while (target[++i])
	{
		word = unset_word(target[i]);
		if (ft_strnstr(target[i], arg, len)
			&& !ft_strncmp(arg, word, ft_strlen(word)))
			continue ;
		str[++j] = ft_strdup(target[i]);
		free (word);
	}
	str[j] = NULL;
	ft_freetwo(target);
	return (str);
}

t_vr	*unset(char **cmd, t_vr *vr)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		vr->env = unset_ut(cmd[i], vr->env, ft_strlen(cmd[i]));
		vr->export = unset_ut(cmd[i], vr->export, ft_strlen(cmd[i]) + 11);
	}
	exitcode = 0;
	return (vr);
}

char	*unset_word(char *target)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(500);
	while (target[i] && target[i] != '=')
	{
		str[i] = target[i];
		i++;
	}
	return (str);
}
