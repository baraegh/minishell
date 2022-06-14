/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 23:49:54 by ael-bach          #+#    #+#             */
/*   Updated: 2022/06/14 23:54:05 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	print_n_echo(char **cmd, int fd, int i)
{
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], fd);
		if (cmd[i])
			ft_putchar_fd(' ', fd);
	}
}
