/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:20:49 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/06 15:54:05 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

char	*ft_getpath(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] && !path)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
		i++;
	}
	if (!path)
	{
		perror("CMD NOT FOUND");
		exit(127);
	}
	return (ft_substr(path, 5, ft_strlen(path) - 5));
}

char	**get_path_splited(char **envp)
{
	char **env;

	env = ft_split(ft_getpath(envp),':');
	if(!env)
	{
		printf("CMD NOT FOUND\n");
		exit (127);
	}
	return (env);
}

char	*ft_checkaccess(char *cmd, char **env)
{
	int		res;
	int		i;
	char	*check;

	i = 0;
	res = 1;
	while (env[i] && res != 0)
	{
		env[i] = ft_strjoin(env[i], "/");
		check = ft_strjoin(env[i], cmd);
		res = access(check, X_OK);
		i++;
	}	
	return (check);
}

int	*openfile(t_cmd *list)
{
	int *fd;
	int i;
	t_cmd	*tmp;

	tmp = list;
	
	i = 0;
	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 0;
	while (tmp->file)
	{
		if (tmp->file->type == 2)
		{
			fd[1] = open(tmp->file->file_name, O_RDWR | O_CREAT | O_TRUNC,0644);
			if (fd < 0)
			{
				printf("no permessions");
				exitcode = 1;
			}
		}
		if (tmp->file->type == 4)
		{
			fd[1] = open(tmp->file->file_name, O_RDWR | O_CREAT | O_APPEND ,0644);
			if (fd < 0)
			{
				printf("no permessions");
				exitcode = 1;
			}
		}
		if (tmp->file->type == 3)
		{
			fd[0] = open(tmp->file->file_name, O_RDONLY ,0644);
			if (fd < 0)
			{
				printf("no permessions");
				exitcode = 1;
			}
		}
		if (tmp->file->type == 5)
		{
			fd[0] = heredoc(tmp->file->file_name);
		}
		tmp->file = tmp->file->next;
	}
	return (fd);
}

void	ft_child(t_cmd *list, t_vr *vr, t_exec_p *exec)
{
	char *cmd;

	if (exec->fd[0] != 0)
		dup2(exec->fd[0], 0);
	else
		dup2(exec->fd_in, 0);
	if (exec->fd[1]  != 0)
		dup2(exec->fd[1], 1);
	else if(list->next)
		dup2(exec->p[1], 1);
	if (in_builtin(list))
	{
		exec_builtin(list, vr, 1);
		exit(exitcode);
	}
	if (access(list->cmd[0], X_OK) && !in_builtin(list))
	{
		cmd = ft_checkaccess(list->cmd[0], get_path_splited(vr->env));
		ft_strlcpy(list->cmd[0],cmd, (size_t)ft_strlen(cmd) + 1);
		free (cmd);
	}
	close(exec->p[0]);
	close(exec->p[1]);
	if (!in_builtin(list))
	{
		if (execve(list->cmd[0], list->cmd, NULL) < 0)
		{
			perror("");
			exit (1);
		}
	}
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

void	exec_pipe(t_cmd *list, t_vr *vr)
{
	t_exec_p *exec;
	int		pipe_num;

	if(!list)
		return ;
	exec = malloc(sizeof(t_exec_p));
	exec->cmdnbr = 0;
	list->pipe_num = ft_lstlen(list);
	pipe_num = list->pipe_num;
	exec->fd_in = 0;
	while(list)
	{
		exec->fd = openfile(list);
		list->pipe_num = pipe_num;
		if(!list->next && in_builtin(list) )
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
				// waitpid(0,NULL,0);
				close(exec->p[1]);
				exec->fd_in = exec->p[0];
			}
		}
		list = list->next;
		exec->cmdnbr++;
	}
	int  i = -1;
	while (++i < pipe_num)
		waitpid(0,NULL,0);
	free (exec->fd);
	free (exec);
}
