/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:12:26 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/17 18:18:21 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	heredoc_utls(t_v v)
{
	free (v.rd);
	close (v.fd[1]);
	g_data.flag = 0;
	close(0);
	dup(g_data.fd);
	return (v.fd[0]);
}

int	heredoc(char *file_name)
{
	t_v	v;

	g_data.flag = 1;
	g_data.h_sig = 1;
	if (pipe(v.fd) < 0)
		ft_error("Permission denied\n", 1);
	v.rd = readline(">");
	while (1)
	{
		if (!v.rd)
			break ;
		if (ft_strlen(file_name) > ft_strlen(v.rd))
			v.len_h = ft_strlen(file_name);
		else
			v.len_h = ft_strlen(v.rd);
		if (!ft_strncmp(v.rd, file_name, v.len_h))
			break ;
		ft_putstr_fd(v.rd, v.fd[1]);
		ft_putstr_fd("\n", v.fd[1]);
		free(v.rd);
		v.rd = readline(">");
	}
	return (heredoc_utls(v));
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
	int	flag;

	flag = 0;
	if (!ft_strncmp(list->cmd[1], "-n", 2))
	{
		i = 0;
		while (list->cmd[++i])
		{
			if (!check_arg(list->cmd[i]))
			{
				if (i == 1)
					flag = 1;
				print_n_echo(list->cmd, fd, i);
				if (flag == 1)
					ft_putstr_fd("\n", fd);
				return ;
			}
		}
	}
	else
		print_echo(list->cmd, fd);
	g_data.exitcode = 0;
}
