/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:12:47 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/30 18:33:26 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_token	*lexer_handle_dollar(t_lexer *lexer)
{
	char	c;

	if (lexer_advance(lexer))
	{
		c = lexer->c;
		if (lexer->c =='"' || lexer->c == '\'')
			return (init_token(TOKEN_WORD, lexer_get_value_in_quote(lexer, c)));
		// if ()
	}
	return (NULL);
}