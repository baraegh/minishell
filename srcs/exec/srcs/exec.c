/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:20:49 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/09 11:17:52 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	*openfile_ut(t_file *file,	int *fd)
{
	if (file->type == 2)
	{
		fd[1] = open(file->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			ft_error("no permessions", 1);
	}
	if (file->type == 4)
	{
		fd[1] = open(file->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd[1] < 0)
			ft_error("no permessions", 1);
	}
	if (file->type == 3)
	{
		fd[0] = open(file->file_name, O_RDONLY, 0644);
		if (fd[0] < 0)
			ft_error("no permessions", 1);
	}
	if (file->type == 5)
		fd[0] = heredoc(file->file_name);
	return (fd);
}

int	*openfile(t_cmd *list)
{
	int		*fd;
	t_cmd	*tmp;

	tmp = list;
	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 0;
	while (tmp->file)
	{
		fd = openfile_ut(tmp->file, fd);
		tmp->file = tmp->file->next;
	}
	return (fd);
}

void	ft_child(t_cmd *list, t_vr *vr, t_exec_p *exec)
{
	char	*cmd;

	duplicate_fd(list, exec);
	if (in_builtin(list))
	{
		exec_builtin(list, vr, 1);
		exit(exitcode);
	}
	if (access(list->cmd[0], X_OK) && !in_builtin(list))
	{
		cmd = ft_checkaccess(list->cmd[0], get_path_splited(vr->env));
		ft_strlcpy(list->cmd[0], cmd, (size_t)ft_strlen(cmd) + 1);
		free (cmd);
	}
	close(exec->p[0]);
	close(exec->p[1]);
	if (!in_builtin(list))
	{
		if (execve(list->cmd[0], list->cmd, vr->env) < 0)
			ft_error("minishell : command not found", 1);
	}
}

void	exec_pipe_ut(t_cmd *list, t_exec_p *exec, t_vr *vr, int pipe_num)
{
	exec->fd = openfile(list);
	list->pipe_num = pipe_num;
	if (!list->next && in_builtin(list))
	{
		if (exec->fd[1] != 0)
			exec_builtin(list, vr, exec->fd[1]);
		else
			exec_builtin(list, vr, 1);
	}
	else
	{
		pipe(exec->p);
		exec->pid = fork();
		if (exec->pid == 0)
			ft_child(list, vr, exec);
		else
		{
			close(exec->p[1]);
			exec->fd_in = exec->p[0];
		}
	}
}

void	exec_pipe(t_cmd *list, t_vr *vr)
{
	t_exec_p	*exec;
	int			pipe_num;
	int			i;

	if (!list)
		return ;
	exec = malloc(sizeof(t_exec_p));
	exec->cmdnbr = 0;
	pipe_num = ft_lstlen(list);
	exec->fd_in = 0;
	while (list)
	{
		exec_pipe_ut(list, exec, vr, pipe_num);
		list = list->next;
		exec->cmdnbr++;
		free (exec->fd);
	}
	i = -1;
	while (++i < pipe_num)
		waitpid(0, NULL, 0);
	free (exec);
}
