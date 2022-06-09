/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:27:52 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/09 14:29:51 by eel-ghan         ###   ########.fr       */
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
	char	*s;

	if (lexer_advance(lexer))
	{
		if (lexer->c == '>' || lexer->c == '<')
			return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
		else
		{
			lexer_skip_whitespace(lexer);
			if (!lexer->c || lexer->c == '|')
				return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
			token = lexer_get_next_token(lexer);
			s = token->value;
			free(token);
			return (init_token(TOKEN_APPEND, s));
		}
	}
	if (lexer->c == ' ')
	{
		lexer_skip_whitespace(lexer);
		return (init_token(TOKEN_OUTPUT, lexer_get_value(lexer)));
	}
	return (NULL);
}

char	*get_here_doc_limit(t_lexer *lexer)
{
	char	*s;
	char	*value;
	char	c;

	if (lexer->c == '$')
	{
		lexer_advance(lexer);
		if (lexer->c != '"' && lexer->c != '\'')
			lexer_back(lexer);
	}
	if (lexer->c == '"' || lexer->c == '\'')
		c = lexer->c;
	else
		c = '\0';
	value = ft_calloc(1, sizeof(char));
	if (!value)
		return (NULL);
	while (lexer->c && lexer->c != ' ')
	{
		if (lexer->c == c)
		{
			lexer_advance(lexer);
			continue ;
		}
		s = lexer_get_char_as_str(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	return (value);
}

t_token	*handle_heredoc_in_red(t_lexer *lexer)
{
	char	*limit;

	if (lexer_advance(lexer))
	{
		if (lexer->c == '>' || lexer->c == '<')
			return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
		else
		{
			lexer_skip_whitespace(lexer);
			if (!lexer->c || lexer->c == '|')
				return (init_token(TOKEN_ERROR, REDIRECTION_ERROR));
			limit = get_here_doc_limit(lexer);
			return (init_token(TOKEN_HERE_DOC, limit));
		}
	}
	if (lexer->c == ' ')
	{
		lexer_skip_whitespace(lexer);
		return (init_token(TOKEN_INPUT, lexer_get_value(lexer)));
	}
	return (NULL);
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
