/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:20:00 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/11 17:38:13 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	cd(t_cmd *list)
{
	if (list->cmd[0] && !list->cmd[1])
	{
		if (chdir("/Users/ael-bach") < 0)
		{
			ft_error("cd : no such file or directory\n", 1);
			return ;
		}
	}
	else if (chdir(list->cmd[1]) < 0)
	{
		ft_error("cd : no such file or directory\n", 1);
		return ;
	}
	g_exitcode = 0;
}

void	pwd(int fd)
{
	char	cwd[1000];

	if (!getcwd(cwd, sizeof(cwd)))
		ft_error("pwd error\n", 1);
	else
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
		g_exitcode = 0;
	}
}

int	in_builtin(t_cmd *list)
{
	char	*str;
	char	**arr;
	int		i;
	int		len;

	if (!list)
		return (0);
	str = "echo cd pwd export unset env exit $?\
	 /bin/pwd /usr/bin/cd /usr/bin/env /bin/echo";
	arr = ft_split(str, ' ');
	i = -1;
	while (++i < 12)
	{
		len = (ft_strlen(arr[i]) > ft_strlen(list->cmd[0])) ? ft_strlen(arr[i]) : ft_strlen(list->cmd[0]);
		if (!ft_strncmp(arr[i], list->cmd[0], len))
		{
			ft_freetwo(arr);
			return (1);
		}
	}
	ft_freetwo(arr);
	return (0);
}
