/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:14:53 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/06 17:12:22 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_cmd	*init_struct_cmd()
{
	t_cmd	*cmd_list;

	cmd_list = malloc(sizeof(t_cmd));
	// if (cmd_list)
		// return
	cmd_list->cmd = ft_calloc(1, sizeof(char *));
	cmd_list->file = NULL;
	cmd_list->pipe_num = 0;
	cmd_list->next = NULL;
	return (cmd_list);
}

t_file	*init_file(char *name, int type)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	// if (!file)
		// return
	file->file_name = name;
	file->type = type;
	file->next = NULL;
	return (file);
}
