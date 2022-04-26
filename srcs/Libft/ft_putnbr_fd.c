/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:55:01 by eel-ghan          #+#    #+#             */
/*   Updated: 2021/11/11 12:19:49 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	number;
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	number = '0' + (nb % 10);
	write(fd, &number, 1);
}
