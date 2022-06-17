/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:40:55 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 19:08:18 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

char	**add_arg_to_arr(char **arr, char *arg, int len)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(len, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (arr[i])
	{
		tmp[i] = ft_strdup(arr[i]);
		free(arr[i]);
		i++;
	}
	tmp[i] = ft_strdup(arg);
	free(arr);
	free(arg);
	return (tmp);
}

void	free_file(t_cmd *list, t_file *f_head)
{
	while (list->file)
	{
		f_head = list->file->next;
		free(list->file->file_name);
		free(list->file);
		list->file = f_head;
	}
}

void	free_list(t_cmd *list)
{
	t_cmd	*head;
	t_file	*f_head;
	int		i;

	if (!list)
		return ;
	head = list;
	f_head = list->file;
	while (list)
	{
		head = list->next;
		i = 0;
		while (list->cmd[i])
			free(list->cmd[i++]);
		free(list->cmd);
		free_file(list, f_head);
		free(list);
		list = head;
	}
	free(list);
}

int	check_space(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] > 32)
			return (1);
		i++;
	}
	return (0);
}
