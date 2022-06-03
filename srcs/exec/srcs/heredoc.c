/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 10:12:26 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/03 20:47:16 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

extern int exitcode;

// int		heredoc(t_cmd *list)
// {
// 	char	*rd;
// 	int		fd[3];
// 	t_cmd	*tmp;

// 	tmp = list;
// 	if (pipe(fd) < 0)
// 	{
// 		printf("pipe error");
// 		exit(1);
// 	}
// 	while (tmp->file)
// 	{
// 		if (tmp->file->type == 5)
// 		{
// 			while (strncmp(rd,tmp->file->file_name, ft_strlen(tmp->file->file_name)))
// 			{
// 				rd = readline(">");
// 				ft_putstr_fd(rd, fd[1]);
// 				ft_putstr_fd("\n", fd[1]);
// 			}
// 		}
// 		tmp->file = tmp->file->next;
// 	}
// 	close(fd[1]);
// 	return (fd[0]);
// }

void	echo(t_cmd *list)
{
	int	i;

	if (!ft_strncmp(list->cmd[1], "-n", 2))
	{
		i = 1;
		while(list->cmd[++i])
			ft_putstr_fd(list->cmd[i], 1);
	}
	else
	{
		i = 0;
		while(list->cmd[++i])
			printf("%s\n",list->cmd[i]);
	}
}