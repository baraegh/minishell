/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:12:26 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/10 16:07:43 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	heredoc(char *file_name)
{
	char	*rd;
	int		fd[2];

	if (pipe(fd) < 0)
		ft_error("Permission denied", 1);
	rd = readline(">");
	while (ft_strncmp(rd, file_name, ft_strlen(rd)))
	{
		ft_putstr_fd(rd, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		rd = readline(">");
	}
	close (fd[1]);
	return (fd[0]);
}

int	check_arg(char *arg)
{
	int	i;

	if (arg[0] == '-' && arg[1] == 'n')
	{
		i = 0;
		while (arg[++i])
		{
			if (arg[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

void	print_echo(char **cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (cmd[i + 1])
			ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	echo(t_cmd *list, int fd)
{
	int	i;

	if (!ft_strncmp(list->cmd[1], "-n", 2))
	{
		i = 0;
		while (list->cmd[++i])
		{
			if (!check_arg(list->cmd[i]))
			{
				while (list->cmd[i])
				{
					ft_putstr_fd(list->cmd[i++], fd);
					if (list->cmd[i])
						ft_putchar_fd(' ', fd);
				}
				return ;
			}
		}
	}
	else
		print_echo(list->cmd, fd);
	g_exitcode = 0;
}
