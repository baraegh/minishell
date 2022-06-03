/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:12:56 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/03 20:58:29 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

extern int exitcode;
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
	// vr->envlen = malloc(sizeof(int));
	vr->envlen = i;
	return (vr);
}

void	env(char **cmd,t_vr *vr)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		printf("cd : no such file or directory\n");
		exitcode = 127;
		i++;
	}
	if(i == 1)
	{
		i = -1;
		while (vr->env[++i])
			printf("%s\n",vr->env[i]);
	}
}
void	cd(t_cmd *list)
{
	if (list->cmd[0] && !list->cmd[1])
	{
		if(chdir("/Users/ael-bach") < 0)
		{
			printf("cd : no such file or directory\n");
			exitcode = 1;
			return ;
		}
	}
	else if(chdir(list->cmd[1]) < 0)
	{
		printf("cd : no such file or directory\n");
			exitcode = 1;
		return ;
	}
}

void	pwd()
{
	char	cwd[500];

	if(!getcwd(cwd,sizeof(cwd)))
	{
		perror("");
		exitcode = 1;
	}
	else
		printf("%s\n",cwd);
}

int		exec_builtin(t_cmd *list,t_vr *vr)
{
	if (list->cmd[0])
	{
		if (!ft_strncmp(list->cmd[0], "echo", 4))
			echo(list);
		if (!ft_strncmp(list->cmd[0], "cd", 2))
			cd(list);
		else if (!ft_strncmp(list->cmd[0], "pwd", 3))
			pwd();
		else if (!ft_strncmp(list->cmd[0], "export", 6))
			export(list, vr);
		else if (!ft_strncmp(list->cmd[0], "unset", 5))
			vr  = unset(list->cmd, vr);
		else if (!ft_strncmp(list->cmd[0], "env", 3))
			env(list->cmd, vr);
		else if (!ft_strncmp(list->cmd[0], "exit", 4))
			ft_exit(list);
		else if (!ft_strncmp(list->cmd[0], "$?", 2))
			printf("%d\n",exitcode);
	}
	return(0);
}

int in_builtin(t_cmd *list)
{
	char	arr[8][7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit","$?"};
	int		i;

	i = 0;
	while (i++ < 6)
	{
		// printf("%s\n",arr[i]);
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