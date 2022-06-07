/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:34:22 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/07 18:20:57 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	export(t_cmd *list, t_vr *vr, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (list->cmd[++i])
		check_exp_env(list->cmd[i], vr);
	// vr->env[i] = NULL;
	if (i == 1)
	{
		j = -1;
		while (vr->env[++j])
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(vr->env[j], fd);
			ft_putstr_fd("\n", fd);
		}
	}
}

// char	*export_ut(char *envp)
// {
// 	char	*exp;
// 	int		l;
// 	int		j;

// 	exp = malloc(sizeof(char) * (ft_strlen(envp) + 13));
// 	if (!exp)
// 		ft_error("allocation failde", 1);
// 	ft_strlcpy(exp, "declare -x ", 12);
// 	l = 11;
// 	j = -1;
// 	while (envp[++j])
// 	{
// 		exp[l++] = envp[j];
// 		if (envp[j] == '=')
// 		{
// 			exp = ft_strjoin(exp, "\"");
// 			exp = ft_strjoin(exp, envp + (j + 1));
// 			exp = ft_strjoin(exp, "\"");
// 			break ;
// 		}
// 	}
// 	return (exp);
// }

// char	**fill_export(char **envp, t_vr	*vr)
// {
// 	char	**exp;
// 	int		i;

// 	i = 0;
// 	while (envp[i++])
// 		;
// 	exp = malloc(sizeof(char *) * i);
// 	if (!exp)
// 	{
// 		perror("");
// 		exit (1);
// 	}
// 	i = -1;
// 	while (envp[++i])
// 		exp[i] = export_ut(envp[i]);
// 	exp[i] = NULL;
// 	vr->explen = i;
// 	return (exp);
// }

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
	int	l;

	l = iterate_export(vr, unset_word(cmd));
	if (l > 0)
	{
		free(vr->env[l]);
		vr->env[l] = ft_strdup(cmd);
	}
	else if (ft_strnstr(cmd, "=", ft_strlen(cmd)) && ft_isalpha(cmd[0]))
	{
		vr->env[vr->envlen++] = ft_strdup(cmd);
		vr->env[vr->envlen] = NULL;
	}
	else
		ft_error("not a valid identifier", 1);
}
