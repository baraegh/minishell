/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:40:55 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/30 16:23:31 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

char	**add_arg_to_arr(char **arr, char *arg, int len)
{
	char	**tmp;
	int	i;

	i = 0;
	tmp = ft_calloc(len, sizeof(char *));
	while (arr[i])
	{
		tmp[i] = ft_strdup(arr[i]);
		i++;
	}
	tmp[i] = arg;
	free_arr(arr);
	return (tmp);
}
