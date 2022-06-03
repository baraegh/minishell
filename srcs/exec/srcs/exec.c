/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:20:49 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/03 21:09:42 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	exitcode;

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
				return (NULL);
			}
		}
		else if (tmp->file->type == 4)
		{
			fd[1] = open(tmp->file->file_name, O_RDWR | O_CREAT | O_APPEND ,0644);
			if (fd < 0)
			{
				printf("no permessions");
				return (NULL);
			}
		}
		else if (tmp->file->type == 3)
		{
			fd[0] = open(tmp->file->file_name, O_RDONLY ,0644);
			if (fd < 0)
			{
				printf("no permessions");
				return (NULL);
			}
		}
		tmp->file = tmp->file->next;
	}
	return (fd);
}

/*
if(not the first cmd)
	dup2(fd+(cmdnbr-1*2),0);
if(no last cmd)
	dup2(fd+(cmdnbr*2+1),1);
*/

/*
        if( not first command ){
            if( dup2(pipefds[(commandc-1)*2], 0) < ){
                perror and exit
            }
        }
         child outputs to next command, if it's not
            the last command 
        if( not last command ){
            if( dup2(pipefds[commandc*2+1], 1) < 0 ){
                perror and exit
            }
*/

void	ft_child(t_cmd *list, t_vr *vr, int fp,t_exec_p *exec)
{
	char *cmd;
	(void)fp;
	cmd = ft_checkaccess(list->cmd[0], get_path_splited(vr->env));
	if (exec->fd[0] != 0)
		dup2(exec->fd[0], 0);
	else
		dup2(exec->fd_in, 0);
	if (exec->fd[1] != 0)
		dup2(exec->fd[1], 1);
	else if(list->next)
		dup2(exec->p[1], 1);
	close(exec->p[0]);
	close(exec->p[1]);
	ft_strlcpy(list->cmd[0],cmd, (size_t)ft_strlen(cmd) + 1);
	// free (cmd);
	exec_builtin(list, vr);
	if (in_builtin(list) == 0)
	{
		if (execve(list->cmd[0], list->cmd, NULL) < 0)
		{
			perror("");
			exit (1);
		}
	}
}

int *open_pipe(t_cmd *list)
{
	int	*fd;
	int	i;

	fd = malloc(sizeof(int) * (list->pipe_num * 2));
	if(!fd)
	{
		perror("memory");
		exit (1);
	}
	i = 0;
	while(i < list->pipe_num)
	{
		if(pipe(fd +i*2) < 0)
			perror("couldn't pipe");
		i++;
	}
	return (fd);
}

int	ft_lstlen(t_cmd *lst)
{
	int		len;
	t_cmd	*tmp;

	tmp = lst;
	len = 0;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	exec_pipe(t_cmd *list, t_vr *vr,int  fd_p)
{
	t_exec_p *exec;
	int		pipe_num;

	exec = malloc(sizeof(t_exec_p));
	exec->cmdnbr = 0;
	list->pipe_num = ft_lstlen(list);
	pipe_num = list->pipe_num;
	exec->fd_in = 0;
	while(list)
	{
		exec->fd = openfile(list);
		list->pipe_num = pipe_num;
		if(!list->next && in_builtin(list))
		{
			if (exec->fd[1] >= 3)
				dup2(exec->fd[1],1);
			exec_builtin(list, vr);
			dup2(STDIN_FILENO,1);
		}
		else
		{
			pipe(exec->p);
			exec->pid = fork();
			if (exec->pid == 0 && !in_builtin(list))
				ft_child(list, vr, fd_p,exec);
			else
			{
				waitpid(0,NULL,0);
				close(exec->p[1]);
				exec->fd_in = exec->p[0];
			}
		}
		list = list->next;
		exec->cmdnbr++;
	}
	free (exec->fd);
	free (exec);
}
