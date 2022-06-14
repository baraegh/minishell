/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:05:54 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/13 21:28:26 by ael-bach         ###   ########.fr       */
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
	t_v		v;

	v.i = 0;
	while (target[v.i++])
		;
	str = malloc(sizeof(char *) * v.i + 1);
	v.i = -1;
	v.j = -1;
	while (target[++v.i])
	{
		word = unset_word(target[v.i]);
		if (ft_strnstr(target[v.i], arg, len)
			&& !ft_strncmp(arg, word, ft_strlen(word)) && arg[0] != '_')
		{
			free (word);
			continue ;
		}
		str[++v.j] = ft_strdup(target[v.i]);
		free (word);
	}
	str[++v.j] = NULL;
	ft_freetwo(target);
	return (str);
}

t_vr	*unset(char **cmd, t_vr *vr)
{
	int		i;
	char	*er_msg;

	i = 0;
	while (cmd[++i])
	{
		if ((!ft_isalpha(cmd[i][0]) || !check_cmd(cmd[i])) && cmd[i][0] != '_')
		{
			er_msg = ft_strjoin1(cmd[i], " : not a valid identifier\n");
			ft_error(er_msg, 1);
			free (er_msg);
			return (vr);
		}
		vr->env = unset_ut(cmd[i], vr->env, ft_strlen(cmd[i]));
	}
	g_data.exitcode = 0;
	return (vr);
}

char	*unset_word(char *target)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * 500);
	while (target[i] && target[i] != '=')
	{
		str[i] = target[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
