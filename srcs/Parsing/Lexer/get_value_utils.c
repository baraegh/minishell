/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barae <barae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:39:00 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/13 19:52:15 by barae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

char	*get_value_util00(t_lexer *lexer, char *value, char *s)
{
	s = lexer_get_char_as_str(lexer);
	value = ft_strjoin(value, s);
	lexer_advance(lexer);
	return (value);
}

int	get_value_check(t_lexer *lexer)
{
	if (lexer->c == '>' || lexer->c == '<'
		|| lexer->c == '|')
		return (1);
	if (lexer->c == '"' || lexer->c == '\''
		|| lexer->c == ' ' || lexer->c == '$')
		return (2);
	return (0);
}

char	*get_value_util01(t_lexer *lexer, char *value, char *s)
{
	while (lexer->c != ' ' && lexer->c)
	{
		if (lexer->c == '$')
		{
			s = handle_dollar(lexer);
			if (!s)
			{
				lexer_advance(lexer);
				continue ;
			}
			value = ft_strjoin(value, s);
			if (get_value_check(lexer) == 1)
				return (value);
			if (get_value_check(lexer) == 2)
				continue ;
		}
		else if (lexer->c == '"' || lexer->c == '\'')
			return (ft_strjoin(value, lexer_get_value_skip_quote(lexer, lexer->c)));
		else if (get_value_check(lexer) == 1)
			break ;
		value = get_value_util00(lexer, value, s);
	}
	return (value);
}
