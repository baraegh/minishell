/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_utils01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:43:58 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/14 20:44:28 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	skip_quote_utill(t_lexer *lexer, char **value,
	char *s, char c)
{
	if (lexer->c == '$' && c == '"')
	{
		s = handle_dollar(lexer);
		if (!s)
			return (skip_quote02(lexer, value));
		*value = ft_strjoin(*value, s);
		if (get_value_check(lexer) == 1)
			return (skip_quote03(lexer, 'r'));
		if (get_value_check(lexer) == 2)
			return (skip_quote03(lexer, 'c'));
	}
	if (lexer->c == c)
	{
		lexer_advance(lexer);
		if (lexer->c == ' ' || lexer->c == '|')
			return (skip_quote03(lexer, 'b'));
		else if (ft_isprint(lexer->c))
			return (skip_quote04(lexer, value));
		return (skip_quote03(lexer, 'c'));
	}
}

char	*skip_quote(t_lexer *lexer, char *value,
	char *s, char c)
{
	while (lexer->c)
	{
		skip_quote_utill(lexer, &value, s, c);
		if (lexer->flag == 1)
			return (value);
		else if (lexer->flag == 2)
			continue ;
		else if (lexer->flag == 3)
			break ;
		value = get_value_util00(lexer, value, s);
	}
	return (value);
}
