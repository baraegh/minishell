/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:12:56 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/07 09:37:07 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_vr	*fill_env(char **envp)
{
	t_vr	*vr;
	int		i;

	i = 0;
	vr = malloc(sizeof(t_vr));
	while (envp[i++]);
	vr->env = malloc(sizeof(char *) * i);
	if(!vr->env)
	{
		perror("");
		exitcode = 1;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		vr->env[i] = ft_strdup(envp[i]);
		i++;
	}
	vr->env[i] = NULL;
	vr->envlen = i;
	return (vr);
}

void	env(char **cmd,t_vr *vr, int fd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_error("cd : no such file or directory", 127);
		i++;
	}
	if(i == 1)
	{
		i = -1;
		while (vr->env[++i])
		{
			ft_putstr_fd(vr->env[i], fd);
			ft_putstr_fd("\n", fd);
		}
	}
	exitcode = 0;
}
void	cd(t_cmd *list)
{
	if (list->cmd[0] && !list->cmd[1])
	{
		if(chdir("/Users/ael-bach") < 0)
		{
			ft_error("cd : no such file or directory", 1);
			return ;
		}
	}
	else if(chdir(list->cmd[1]) < 0)
	{
		ft_error("cd : no such file or directory", 1);
		return ;
	}
	exitcode = 0;
}

void	pwd(int fd)
{
	char	cwd[1000];

	if(!getcwd(cwd,sizeof(cwd)))
		ft_error("pwd error", 1);
	else
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
		exitcode = 0;
	}
}

int		exec_builtin(t_cmd *list,t_vr *vr,int fd)
{
	if (list->cmd[0])
	{
		if (!ft_strncmp(list->cmd[0], "echo", ft_strlen("echo"))
			|| !ft_strncmp(list->cmd[0], "/bin/echo", ft_strlen("/bin/echo")))
			echo(list, fd);
		if (!ft_strncmp(list->cmd[0], "cd", 2)
			|| !ft_strncmp(list->cmd[0], "/usr/bin/cd", ft_strlen("/usr/bin/cd")))
			cd(list);
		else if (!ft_strncmp(list->cmd[0], "pwd", 3)
			|| !ft_strncmp(list->cmd[0], "/bin/pwd", ft_strlen("/bin/pwd")))
			pwd(fd);
		else if (!ft_strncmp(list->cmd[0], "export", 6))
			export(list, vr, fd);
		else if (!ft_strncmp(list->cmd[0], "unset", 5))
			vr  = unset(list->cmd, vr);
		else if (!ft_strncmp(list->cmd[0], "env", 3)
			|| !ft_strncmp(list->cmd[0], "/usr/bin/env", ft_strlen("/usr/bin/env")))
			env(list->cmd, vr, fd);
		else if (!ft_strncmp(list->cmd[0], "exit", 4))
			ft_exit(list);
		else if (!ft_strncmp(list->cmd[0], "$?", 2))
			printf("bash: %d: command not found\n",exitcode);
	}
	return(0);
}

int in_builtin(t_cmd *list)
{
	char	arr[12][12] = {"echo", "cd", "pwd", "export", "unset", "env", "exit","$?", "/bin/pwd", "/usr/bin/cd", "/usr/bin/env", "/bin/echo"};
	int		i;

	i = -1;
	while (++i < 12)
	{
		if (!ft_strncmp(arr[i], list->cmd[0], ft_strlen(list->cmd[0])))
		{
			return (1);
			break;	
		}
	}
	return (0);
}

void	 ft_exit(t_cmd *list)
{
	int	i;

	i = 1;
	list->pipe_num +=0; 
	// while (list->cmd[i])
	// {
	// 	if (!ft_atoi(list->cmd[i]))
	// 	{
	// 		printf("exit\nnumeric argument required\n");
	// 		exitcode = ft_atoi(list->cmd[i]) < 0 ? 255 - ft_atoi(list->cmd[i]) * -1 : ft_atoi(list->cmd[i]);
	// 		break;
	// 	}
	// 	if (ft_atoi(list->cmd[i]) && !ft_atoi(list->cmd[i+1]))
	// 	{
	// 		printf("too many arguments\n");
	// 		break;
	// 	}
	// 	i++;
	// }
	// if(i == 1)
	// {
		printf("exit\n");
		// exitcode = 0;
		exit(exitcode);
	// }
	// else
}