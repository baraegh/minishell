/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:45:50 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/13 23:49:32 by eel-ghan         ###   ########.fr       */
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

void	skip_quote02(t_lexer *lexer, char **value)
{
	*value = skip_quote_utill01(lexer, *value);
	lexer->flag = 2;
}

void	skip_quote03(t_lexer *lexer, char c)
{
	if (c == 'r')
		lexer->flag = 1;
	else if (c == 'c')
		lexer->flag = 2;
	else if (c == 'b')
		lexer->flag = 3;
}

void	skip_quote04(t_lexer *lexer, char **value)
{
	*value = ft_strjoin(*value, lexer_get_value(lexer));
	lexer->flag = 1;
}
