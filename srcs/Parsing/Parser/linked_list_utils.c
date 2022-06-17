/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:43:37 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 19:27:09 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_cmd	*t_cmd_last(t_cmd *lst)
{
	t_cmd	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	t_cmd_add_back(t_cmd **cmd_list, t_cmd *new)
{
	t_cmd	*tmp;

	if (cmd_list)
	{
		tmp = t_cmd_last(*cmd_list);
		if (*cmd_list)
			tmp->next = new;
		else
			*cmd_list = new;
	}
}

t_file	*t_file_last(t_file *lst)
{
	t_file	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	t_file_add_back(t_file **file_list, t_file *new)
{
	t_file	*tmp;

	if (file_list)
	{
		tmp = t_file_last(*file_list);
		if (*file_list)
			tmp->next = new;
		else
			*file_list = new;
	}
}
