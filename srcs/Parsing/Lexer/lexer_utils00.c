/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:32:53 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/30 14:16:07 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

char	*lexer_get_char_as_str(t_lexer *lexer)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	// if (!str)
	// 	return
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_collect_pipe(t_lexer *lexer)
{
	if (lexer_advance(lexer))
	{
		if (lexer->c == '|')
			return (init_token(TOKEN_ERROR, PIPE_ERROR));
		lexer_skip_whitespace(lexer);
		if (!lexer->c)
			return (init_token(TOKEN_ERROR, PIPE_ERROR));
	}
	if (lexer->cmd_flag)
		return (init_token(TOKEN_ERROR, PIPE_ERROR));
	lexer->cmd_flag = 1;
	return (init_token(TOKEN_PIPE, "|"));
}

t_token	*lexer_collect_str(t_lexer *lexer)
{
	if (lexer->cmd_flag)
	{
		lexer->cmd_flag = 0;
		return (init_token(TOKEN_CMD, lexer_get_value(lexer)));
	}
	return (init_token(TOKEN_WORD, lexer_get_value(lexer)));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	char	c;

	while (lexer->c != '\0'
		&& lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		if (lexer->c == '|')
			return (lexer_collect_pipe(lexer));
		if (lexer->c == '>')
			return (lexer_collect_out_red(lexer));
		if (lexer->c == '<')
			return (lexer_collect_in_red(lexer));
		// if (lexer->c == '$')
		// 	return (lexer_handle_dollar(lexer));
		if (lexer->c == '"' || lexer->c == '\'')
		{
			c = lexer->c;
			if (!lexer->cmd_flag)
				return (init_token(TOKEN_WORD, lexer_get_value_skip_quote(lexer, c)));
			lexer->cmd_flag = 0;
			return (init_token(TOKEN_CMD, lexer_get_value_skip_quote(lexer, c)));
		}
		if (lexer->c)
			return (lexer_collect_str(lexer));
	}
	return (NULL);
}