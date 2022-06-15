/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 23:32:40 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 18:33:07 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "../srcs/Libft/libft.h"
# include "token.h"
# include "lexer.h"
# include "error.h"
# include "struct_cmd.h"
# include "parser.h"
# include "exec.h"

typedef struct s_data
{
	int	exitcode;
	int	flag;
	int	heredoc;
	int	fd;
	int	exitheredoc;
	int	quit_flag;
	int	here_doc_flag;
	int	rd_error;

}	t_data;

t_data	g_data;

#endif