/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:02:49 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/13 11:53:15 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	*openfile_ut(t_file *file,	int *fd)
{
	if (file->type == 2)
	{
		fd[1] = open(file->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
			ft_error("no permessions\n", 1);
	}
	if (file->type == 4)
	{
		fd[1] = open(file->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd[1] < 0)
			ft_error("no permessions\n", 1);
	}
	if (file->type == 3)
	{
		fd[0] = open(file->file_name, O_RDONLY, 0644);
		if (fd[0] < 0)
			ft_error("no permessions\n", 1);
	}
	if (file->type == 5)
		fd[0] = heredoc(file->file_name);
	return (fd);
}

int	*openfile(t_cmd *list)
{
	int		*fd;
	t_cmd	*tmp;

	tmp = list;
	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 0;
	while (tmp->file)
	{
		fd = openfile_ut(tmp->file, fd);
		tmp->file = tmp->file->next;
	}
	return (fd);
}

void	ft_execve(t_cmd *list, t_vr *vr, char *cmderr)
{
	if (!in_builtin(list))
	{	
		if (execve(list->cmd[0], list->cmd, vr->env) < 0)
		{
			ft_error(ft_strjoin1(ft_strjoin1("minishell : ", cmderr),
					" :command not found\n"), 127);
			free (cmderr);
			exit (127);
		}
	}
}
