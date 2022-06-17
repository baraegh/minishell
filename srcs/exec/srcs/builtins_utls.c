/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:20:00 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/17 18:32:03 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	change_pwdenv(char *oldpwd, t_vr *vr)
{
	char	*pwd;
	char	cwd[1000];

	if (oldpwd)
	{
		pwd = ft_strjoin1("OLDPWD=", oldpwd);
		check_exp_env(pwd, vr);
		free (pwd);
	}
	oldpwd = getcwd(cwd, sizeof(cwd));
	if (oldpwd)
	{
		pwd = ft_strjoin1("PWD=", oldpwd);
		check_exp_env(pwd, vr);
		free (pwd);
	}
}

void	cd(t_cmd *list, t_vr *vr)
{
	char	cwd[1000];
	char	*oldpwd;

	oldpwd = getcwd(cwd, sizeof(cwd));
	if (list->cmd[0] && !list->cmd[1])
	{
		if (chdir(getenv("HOME")) < 0)
		{
			ft_error("cd : no such file or directory\n", 2);
			return ;
		}
	}
	else if (chdir(list->cmd[1]) < 0)
	{
		ft_error("cd : no such file or directory\n", 2);
		return ;
	}
	change_pwdenv(oldpwd, vr);
	g_data.exitcode = 0;
}

void	pwd(int fd)
{
	char	cwd[1000];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_error("Error : 👺 omnytk, rah hna fin segfaultat\n", 2);
	else
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
		g_data.exitcode = 0;
	}
}

int	in_builtin(t_cmd *list)
{
	char	*str;
	char	**arr;
	int		i;
	int		len;

	if (!list->cmd[0])
		return (0);
	str = "echo cd pwd export unset env exit $?\
	 /bin/pwd /usr/bin/cd /usr/bin/env /bin/echo";
	arr = ft_split(str, ' ');
	i = -1;
	while (arr[++i])
	{
		if (ft_strlen(arr[i]) > ft_strlen(list->cmd[0]))
			len = ft_strlen(arr[i]);
		else
			len = ft_strlen(list->cmd[0]);
		if (!ft_strncmp(arr[i], list->cmd[0], len))
		{
			ft_freetwo(arr);
			return (1);
		}
	}
	ft_freetwo(arr);
	return (0);
}
