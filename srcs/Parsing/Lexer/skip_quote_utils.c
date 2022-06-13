/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barae <barae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:45:50 by barae             #+#    #+#             */
/*   Updated: 2022/06/13 19:52:10 by barae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

char	*skip_quote_utill00(t_lexer *lexer, char *value)
{
	value = ft_strjoin(value, ft_strdup("$"));
	lexer_advance(lexer);
	return (value);
}

char	*skip_quote_utill01(t_lexer *lexer, char *value)
{
	if (lexer->c == '$')
		value = skip_quote_utill00(lexer, value);
	return (value);
}

char	*skip_quote(t_lexer *lexer, char *value,
    char *s, char c)
{
	while (lexer->c)
	{
		if (lexer->c == '$' && c == '"')
		{
			s = handle_dollar(lexer);
			if (!s)
			{
				value = skip_quote_utill01(lexer, value);
				continue ;
			}
			value = ft_strjoin(value, s);
			if (get_value_check(lexer) == 1)
				return (value);
			if (get_value_check(lexer) == 2)
				continue ;
		}
		if (lexer->c == c)
		{
			lexer_advance(lexer);
			if (lexer->c == ' ' || lexer->c == '|')
				break ;
			else if (ft_isprint(lexer->c))
				return (ft_strjoin(value, lexer_get_value(lexer)));
			continue ;
		}
		value = get_value_util00(lexer, value, s); 
	}
	return (value);
}
