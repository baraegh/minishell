/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:34:22 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/03 20:47:11 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

extern int exitcode;

void	export(t_cmd *list, t_vr *vr)
{
	int	i;
	int	j;

	i = 0;
	while (list->cmd[++i])
	{
		if(ft_strnstr(list->cmd[i], "=", ft_strlen(list->cmd[i])))
		{
			vr->env[vr->envlen++] = ft_strdup(list->cmd[i]);
			vr->export[vr->explen++] = export_ut(list->cmd[i]);

		}
		else
			vr->export[vr->explen++] = export_ut(list->cmd[i]);
	}
	vr->env[vr->envlen] = NULL;
	vr->export[vr->explen] = NULL;
	if (i == 1)
	{
		j = -1;
		while (vr->export[++j])
			printf("%s\n",vr->export[j]);
	}
	// for(int i = 0;vr->env[i];i++)
	// 	printf("%s\n",vr->env[i]);
	// printf("********************************************\n");
	// for(int i = 0;vr->export[i];i++)
	// 	printf("%s\n",vr->export[i]);
}

char *export_ut(char *envp)
{
	char	*exp;
	int		l;
	int		j;

	exp = malloc(sizeof(char) * (ft_strlen(envp) + 13));
	if(!exp)
	{
		perror("");
		exit (1);
	}
	ft_strlcpy(exp,"declare -x ",12);
	l = 11;
	j = -1;
	while (envp[++j])
	{
		exp[l++] = envp[j];
		if(envp[j] == '=')
		{
			exp = ft_strjoin(exp,"\"");
			exp = ft_strjoin(exp,envp + (j + 1));
			exp = ft_strjoin(exp,"\"");
			break ;
		}
	}
	return (exp);
}

char **fill_export(char **envp, t_vr	*vr)
{
	char	**exp;
	int		i;

	i = 0;
	while (envp[i++]);
	exp = malloc(sizeof(char *) * i);
	if(!exp)
	{
		perror("");
		exit (1);
	}
	i = -1;
	while (envp[++i])
		exp[i] = export_ut(envp[i]);
	exp[i] = NULL;
	// vr->explen = malloc(sizeof(int));
	vr->explen = i;
	return (exp);
}