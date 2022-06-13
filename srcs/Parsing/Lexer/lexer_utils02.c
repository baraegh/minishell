/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:28:24 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/12 21:58:26 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

void	get_here_doc_limit_util(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c != '"' && lexer->c != '\'')
		lexer_back(lexer);
}

char	*get_limit_value(t_lexer *lexer, char *s, char *value)
{
	s = lexer_get_char_as_str(lexer);
	value = ft_strjoin(value, s);
	lexer_advance(lexer);
	return (value);
}

t_token	*handle_red_with_quote(t_lexer *lexer, char c)
{
	char	*value;
	t_token	*token;

	value = lexer_get_value_in_quote(lexer, c);
	if (lexer->c == c)
		lexer_skip_quote(lexer);
	token = init_token(TOKEN_OUTPUT,
			ft_strjoin(value, lexer_get_value(lexer)));
	return (token);
}
