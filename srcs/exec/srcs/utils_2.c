/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:02:18 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/13 21:28:26 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	closepipe_andwait(t_exec_p *exec, t_v *v)
{
	v->i = 0;
	while (v->i < v->pipe_num * 2)
		close(exec->p[v->i++]);
	v->i = 0;
	while (v->i < v->pipe_num)
	{
		waitpid(0, &v->status, 0);
		if (!in_builtin(v->tmp))
			g_data.exitcode = WEXITSTATUS(v->status);	
		v->tmp = v->tmp->next;
		v->i++;
	}
	free(exec->p);
	free (exec);
}
