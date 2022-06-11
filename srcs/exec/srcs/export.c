/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:34:22 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/11 18:43:24 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	check_cmd(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (!ft_isalnum(cmd[i]))
			return (0);
	}
	return (1);
}

void	print_export(char *s, int fd)
{
	int		i;
	int		l;

	i = 0;
	while (s[i] && s[i - 1] != '=')
		ft_putchar_fd(s[i++], fd);
	l = i - 1;
	if (s[l] == '=')
	{
		ft_putchar_fd('\"', fd);
		while (s[i])
			ft_putchar_fd(s[i++], fd);
		ft_putchar_fd('\"', fd);
	}
}

void	export(t_cmd *list, t_vr *vr, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (list->cmd[++i])
		check_exp_env(list->cmd[i], vr);
	if (i == 1)
	{
		j = 0;
		while (vr->env[++j])
		{
			ft_putstr_fd("declare -x ", fd);
			print_export(vr->env[j], fd);
			ft_putstr_fd("\n", fd);
		}
		g_exitcode = 0;
	}
}

int	iterate_export(t_vr *vr, char *target)
{
	int	i;

	i = -1;
	while (vr->env[++i])
	{
		if (!ft_strncmp(vr->env[i], target, ft_strlen(target)))
			return (i);
	}
	return (-1);
}

void	check_exp_env(char *cmd, t_vr *vr)
{
	int		l;
	char	*word;

	word = unset_word(cmd);
	l = iterate_export(vr, word);
	if (l > 0 && ft_strnstr(cmd, "=", ft_strlen(cmd)) && check_cmd(word))
	{
		free(vr->env[l]);
		vr->env[l] = ft_strdup(cmd);
	}
	else if (ft_strnstr(cmd, "=", ft_strlen(cmd))
		&& ft_isalpha(cmd[0]) && check_cmd(word))
	{
		vr->env[vr->envlen] = ft_strdup(cmd);
		vr->envlen += 1;
		vr->env[vr->envlen] = NULL;
	}
	else
		ft_error("not a valid identifier\n", 1);
	free (word);
	g_exitcode = 0;
}
