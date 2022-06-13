/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/12 21:22:37 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	check_char(t_lexer *lexer)
{
	if ((lexer->c < 'a' || lexer->c > 'z')
		&& (lexer->c < 'A' || lexer->c > 'Z')
		&& (lexer->c < '0' || lexer->c > '9')
		&& lexer->c != '_' && lexer->c != '$')
		return (1);
	if (lexer->c == '>' || lexer->c == '<'
		|| lexer->c == '|')
		return (1);
	return (0);
}

char	*get_value_for_dollar(t_lexer *lexer)
{
	char	*s;
	char	*value;

	if ((lexer->c < 'a' || lexer->c > 'z')
		&& (lexer->c < 'A' || lexer->c > 'Z')
		&& (lexer->c < '0' || lexer->c > '9')
		&& lexer->c != '_')
		return (get_str2(lexer));
	s = get_str(lexer);
	value = get_env(lexer->vr, s);
	free(s);
	if (!value)
	{
		value = ft_calloc(1, sizeof(char));
		if (!value)
			return (NULL);
	}
	return (value);
}
