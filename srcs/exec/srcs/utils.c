/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:19:28 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/14 16:19:17 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	ft_error(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	g_data.exitcode = exit_code;
}

int	ft_lstlen(t_cmd *lst)
{
	int		len;
	t_cmd	*tmp;

	tmp = lst;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	duplicate_fd(t_cmd *list, t_exec_p *exec)
{
	if (exec->fd[0] != 0)
		dup2(exec->fd[0], 0);
	else if (exec->cmdnbr != 0)
		dup2(exec->p[(exec->cmdnbr - 1) * 2], 0);
	if (exec->fd[1] != 0)
		dup2(exec->fd[1], 1);
	else if (list->next)
		dup2(exec->p[exec->cmdnbr * 2 + 1], 1);
}

char	**add_to_export(char **env, char *elmnt)
{
	char	**s_env;
	int		i;

	i = 0;
	while (env[i++])
		;
	s_env = malloc(sizeof(char *) * i + 1);
	if (!s_env)
		ft_error("allocation faild\n", 1);
	i = -1;
	while (env[++i])
		s_env[i] = ft_strdup(env[i]);
	s_env[i++] = ft_strdup(elmnt);
	s_env[i] = NULL;
	ft_freetwo(env);
	return (s_env);
}
