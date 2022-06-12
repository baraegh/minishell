/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:20:49 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/12 19:55:01 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	ft_child(t_cmd *list, t_vr *vr, t_exec_p *exec)
{
	char	*cmd;
	char	*cmderr;
	int		i;

	if (!list->cmd[0])
		return ;
	cmderr = ft_strdup(list->cmd[0]);
	duplicate_fd(list, exec);
	if (in_builtin(list))
	{
		exec_builtin(list, vr, 1);
		exit(0);
	}
	if (access(list->cmd[0], X_OK) && !in_builtin(list))
	{
		cmd = ft_checkaccess(list->cmd[0], get_path_splited(vr->env));
		ft_strlcpy(list->cmd[0], cmd, (size_t)ft_strlen(cmd) + 1);
		free (cmd);
	}
	i = 0;
	while (i < list->pipe_num * 2)
		close(exec->p[i++]);
	ft_execve(list, vr, cmderr);
}

void	exec_pipe_ut(t_cmd *list, t_exec_p *exec, t_vr *vr, int pipe_num)
{
	exec->fd = openfile(list);
	list->pipe_num = pipe_num;
	if (!list->next && in_builtin(list) && exec->cmdnbr == 0)
	{
		if (exec->fd[1] != 0)
			vr = exec_builtin(list, vr, exec->fd[1]);
		else
			vr = exec_builtin(list, vr, 1);
	}
	else
	{
		exec->pid = fork();
		if (exec->pid == 0)
			ft_child(list, vr, exec);
	}
}

void	exec_pipe(t_cmd *list, t_vr *vr)
{
	t_exec_p	*exec;
	t_v			v;

	if (!list)
		return ;
	v.tmp = list;
	exec = malloc(sizeof(t_exec_p));
	exec->cmdnbr = 0;
	v.pipe_num = ft_lstlen(list);
	exec->p = malloc(sizeof(int) * v.pipe_num * 2);
	v.i = -1;
	while (++v.i < v.pipe_num)
		pipe(exec->p + v.i * 2);
	exec->fd_in = 0;
	while (list)
	{
		exec_pipe_ut(list, exec, vr, v.pipe_num);
		list = list->next;
		exec->cmdnbr++;
		free(exec->fd);
	}
	v.i = 0;
	while (v.i < v.pipe_num * 2)
		close(exec->p[v.i++]);
	v.i = 0;
	while (v.i < v.pipe_num)
	{
		waitpid(0, &v.status, 0);
		g_exitcode = WEXITSTATUS(v.status);
		v.i++;
	}
	free(exec->p);
	free (exec);
}
