/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:19:28 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/07 12:04:42 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	ft_error(char *msg, int exit_code)
{
	perror(msg);
	exitcode = exit_code;
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
	else
		dup2(exec->fd_in, 0);
	if (exec->fd[1] != 0)
		dup2(exec->fd[1], 1);
	else if (list->next)
		dup2(exec->p[1], 1);
}
