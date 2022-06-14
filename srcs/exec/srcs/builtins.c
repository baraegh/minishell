/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:12:56 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/13 21:28:26 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_vr	*fill_env(char **envp)
{
	t_vr	*vr;
	int		i;

	i = 0;
	vr = malloc(sizeof(t_vr));
	while (envp[i++])
		;
	vr->env = malloc(sizeof(char *) * i);
	if (!vr->env)
		ft_error("allocation faild\n", 1);
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

void	env(char **cmd, t_vr *vr, int fd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_error("env : no such file or directory\n", 127);
		return ;
		i++;
	}
	if (i == 1)
	{
		i = -1;
		while (vr->env[++i])
		{
			if (ft_strchr(vr->env[i], '='))
			{
				ft_putstr_fd(vr->env[i], fd);
				ft_putstr_fd("\n", fd);
			}
		}
	}
	g_data.exitcode = 0;
}

t_vr	*exec_builtin(t_cmd *list, t_vr *vr, int fd)
{
	if (list->cmd[0])
	{
		if (!ft_strncmp(list->cmd[0], "echo", ft_strlen("echo"))
			|| !ft_strncmp(list->cmd[0], "/bin/echo", ft_strlen("/bin/echo")))
			echo(list, fd);
		if (!ft_strncmp(list->cmd[0], "cd", 2)
			|| !ft_strncmp(list->cmd[0], "/usr/bin/cd", \
			ft_strlen("/usr/bin/cd")))
			cd(list);
		else if (!ft_strncmp(list->cmd[0], "pwd", 3)
			|| !ft_strncmp(list->cmd[0], "/bin/pwd", ft_strlen("/bin/pwd")))
			pwd(fd);
		else if (!ft_strncmp(list->cmd[0], "export", 6))
			export(list, vr, fd);
		else if (!ft_strncmp(list->cmd[0], "unset", 5))
			vr = unset(list->cmd, vr);
		else if (!ft_strncmp(list->cmd[0], "env", 3)
			|| !ft_strncmp(list->cmd[0], "/usr/bin/env", \
			ft_strlen("/usr/bin/env")))
			env(list->cmd, vr, fd);
		else if (!ft_strncmp(list->cmd[0], "exit", 4))
			ft_exit(list);
	}
	return (vr);
}

int	ft_exit_2(t_cmd *list)
{
	int	i;
	int	ext;

	i = 0;
	while (list->cmd[++i])
	{
		if (!ft_atoi(list->cmd[i]))
		{
			printf("exit\nexit : numeric argument required\n");
			g_data.exitcode = 255;
			exit (g_data.exitcode);
		}
		else if (ft_atoi(list->cmd[i]) && !list->cmd[i + 1])
		{
			ext = ft_atoi(list->cmd[i]);
			ft_error("exit\n", ft_atoi(list->cmd[i]));
			exit (ext);
		}
		else if (ft_atoi(list->cmd[i]) && ft_atoi(list->cmd[i + 1]))
		{
			ft_error("exit : too many arguments\n", 1);
			return (-1);
		}
	}
	return (i);
}

void	ft_exit(t_cmd *list)
{
	int	i;

	i = ft_exit_2(list);
	if (i == 1)
	{
		printf("exit\n");
		g_data.exitcode = 0;
		exit(g_data.exitcode);
	}
}
