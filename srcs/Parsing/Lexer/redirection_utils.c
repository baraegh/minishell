/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:27:52 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/29 17:41:44 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_token	*lexer_collect_out_red(t_lexer *lexer)
{
	t_token	*token;

	if (!lexer_advance(lexer))
		return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
	if (lexer->c == '>')
	{
		token = handle_append_out_red(lexer);
		if (token != NULL)
			return (token);
	}
	else if (lexer->c == '<')
		return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
	else if (lexer->c == '"' || lexer->c == '\'')
		return (handle_red_with_quote(lexer, lexer->c));
	lexer_skip_whitespace(lexer);
	if (!lexer->c)
		return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
	return (init_token(TOKEN_OUTPUT, lexer_get_value(lexer)));
}

t_token	*lexer_collect_in_red(t_lexer *lexer)
{
	t_token	*token;

	if (!lexer_advance(lexer))
		return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
	if (lexer->c == '<')
	{
		token = handle_heredoc_in_red(lexer);
		if (token != NULL)
			return (token);
	}
	else if (lexer->c == '>')
		return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
	else if (lexer->c == '"' || lexer->c == '\'')
		return (handle_red_with_quote(lexer, lexer->c));
	lexer_skip_whitespace(lexer);
	if (!lexer->c)
		return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
	return (init_token(TOKEN_INPUT, lexer_get_value(lexer)));
}

t_token	*handle_append_out_red(t_lexer *lexer)
{
	t_token *token;

	if (lexer_advance(lexer))
	{
		if (lexer->c == '>' || lexer->c == '<')
		{
			// free(token);
			// free(lexer);
			return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
		}
		else
		{
			lexer_skip_whitespace(lexer);
			if (!lexer->c || lexer->c == '|')
				return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
			token = lexer_get_next_token(lexer);
			return (init_token(TOKEN_APPEND, token->value));
		}
	}
	if (lexer->c == ' ')
	{
		lexer_skip_whitespace(lexer);
		return (init_token(TOKEN_OUTPUT, lexer_get_value(lexer)));
	}
	return (NULL);
}

t_token	*handle_heredoc_in_red(t_lexer *lexer)
{
	t_token	*token;

	if (lexer_advance(lexer))
	{
		if (lexer->c == '>' || lexer->c == '<')
		{
			// free(token);
			// free(lexer);
			return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
		}
		else
		{
			lexer_skip_whitespace(lexer);
			if (!lexer->c || lexer->c == '|')
				return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
			token = lexer_get_next_token(lexer);
			return (init_token(TOKEN_HERE_DOC, token->value));
		}
	}
	if (lexer->c == ' ')
	{
		lexer_skip_whitespace(lexer);
		return (init_token(TOKEN_INPUT, lexer_get_value(lexer)));
	}
	return (NULL);;
}

t_token	*handle_red_with_quote(t_lexer *lexer, char c)
{
	char	*value;

	value = lexer_get_value_in_quote(lexer, c);
	if (lexer->c == c)
		lexer_skip_quote(lexer);
	return (init_token(TOKEN_OUTPUT, ft_strjoin(value, lexer_get_value(lexer))));
}

