/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:12:26 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/05 15:39:04 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	heredoc(char *file_name)
{
	char	*rd = NULL;
	int		fd[2];

	if(pipe(fd) < 0)
	{
		printf("Permission denied\n");
		exitcode = 1;
	}
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

void	echo(t_cmd *list, int fd)
{
	int	i;

	if (!ft_strncmp(list->cmd[1], "-n", 2))
	{
		i = 1;
		while(list->cmd[++i])
			ft_putstr_fd(list->cmd[i], fd);
	}
	else
	{
		i = 0;
		while(list->cmd[++i])
		{
			ft_putstr_fd(list->cmd[i],fd);
			ft_putstr_fd("\n",fd);
		}
	}
}