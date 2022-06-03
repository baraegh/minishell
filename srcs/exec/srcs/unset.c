/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:05:54 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/03 20:47:23 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

extern int exitcode;

char	**unset_ut(char *arg, char **target, int len)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	while (target[i++]);
	str = malloc(sizeof(char *) * i);
	if(!str)
	{
		perror("allocation failde");
		exit (1);
	}
	i = -1;
	j = -1;
	while (target[++i])
	{
		if(ft_strnstr(target[i], arg, len))
			continue;
		str[++j] = ft_strdup(target[i]);
	}
	str[j] = NULL;
	// ft_freetwo(target);
	return (str);
}

t_vr	*unset(char **cmd, t_vr *vr)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		vr->env = unset_ut(cmd[i], vr->env,ft_strlen(cmd[i]));
		vr->export = unset_ut(cmd[i], vr->export, ft_strlen(cmd[i]) + 11);
	}
	return (vr);
}