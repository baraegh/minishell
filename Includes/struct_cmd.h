/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:15:42 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/08 19:11:12 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CMD_H
# define STRUCT_CMD_H

typedef struct s_cmd t_cmd;
typedef struct s_file t_file;

struct s_file
{
	char	*file_name;
	int		type;
	t_file	*next;
};

struct s_cmd
{
	char	**cmd;
	t_file	*file;
	t_cmd 	*next;
};

t_cmd	*init_struct_cmd();
t_file	*init_file(char *name, int type);
t_cmd	*t_cmd_last(t_cmd *lst);
void	t_cmd_add_back(t_cmd **cmd_list, t_cmd *new);
t_file	*t_file_last(t_file *file);
void	t_file_add_back(t_file **file_list, t_file *new);

# endif

