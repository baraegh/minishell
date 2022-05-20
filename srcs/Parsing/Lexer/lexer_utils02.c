/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:33:59 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/19 18:34:29 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_token	*lexer_collect_out_red(t_lexer *lexer)
{
	t_token	*token;
	char	*value = NULL;

	if (!lexer_advance(lexer))
		return (init_token(TOKEN_ERROR, ERROR));
	if (lexer->c == '>')
	{
		if (lexer_advance(lexer))
		{
			if (lexer->c == '>' || lexer->c == '<')
			{
				// free(token);
				// free(lexer);
				return (init_token(TOKEN_ERROR, ERROR));
			}
			else
			{
				lexer_skip_whitespace(lexer);
				lexer_back(lexer);
				token = lexer_get_next_token(lexer);
				return (init_token(TOKEN_APPEND, token->value));
			}
		}
		if (lexer->c == ' ')
		{
			lexer_skip_whitespace(lexer);
			return (init_token(TOKEN_OUTPUT, lexer_get_value(lexer)));
		}
	}
	else if (lexer->c == '<')
		return (init_token(TOKEN_ERROR, ERROR));
	else if (lexer->c == '"')
	{
		value = lexer_get_value_in_quote(lexer, '"');
		if (lexer->c == '"')
			lexer_skip_quote(lexer);
		if (!lexer->c
			&& (!ft_strncmp(value, ">", ft_strlen(value))
				|| !ft_strncmp(value, "<", ft_strlen(value))))
			return (init_token(TOKEN_ERROR, ERROR));
		return (init_token(TOKEN_OUTPUT, ft_strjoin(value, lexer_get_value(lexer))));
	}
	else if (lexer->c == '\'')
	{
		value = lexer_get_value_in_quote(lexer, '\'');
		if (lexer->c == '\'')
			lexer_skip_quote(lexer);
		if (!lexer->c
			&& (!ft_strncmp(value, ">", ft_strlen(value))
				|| !ft_strncmp(value, "<", ft_strlen(value))))
			return (init_token(TOKEN_ERROR, ERROR));
		return (init_token(TOKEN_OUTPUT, ft_strjoin(value, lexer_get_value(lexer))));
	}
	lexer_skip_whitespace(lexer);
	if (!lexer->c)
		return (init_token(TOKEN_ERROR, ERROR));
	return (init_token(TOKEN_OUTPUT, lexer_get_value(lexer)));
}

t_token	*lexer_collect_in_red(t_lexer *lexer)
{
	t_token	*token;

	char	*value = NULL;

	if (!lexer_advance(lexer))
		return (init_token(TOKEN_ERROR, ERROR));
	if (lexer->c == '>')
	{
		if (lexer_advance(lexer))
		{
			if (lexer->c == '>' || lexer->c == '<')
			{
				// free(token);
				// free(lexer);
				return (init_token(TOKEN_ERROR, ERROR));
			}
			else
			{
				lexer_skip_whitespace(lexer);
				lexer_back(lexer);
				token = lexer_get_next_token(lexer);
				return (init_token(TOKEN_HERE_DOC, token->value));
			}
		}
		if (lexer->c == ' ')
		{
			lexer_skip_whitespace(lexer);
			return (init_token(TOKEN_INPUT, lexer_get_value(lexer)));
		}
	}
	else if (lexer->c == '<')
		return (init_token(TOKEN_ERROR, ERROR));
	else if (lexer->c == '"')
	{
		value = lexer_get_value_in_quote(lexer, '"');
		if (lexer->c == '"')
			lexer_skip_quote(lexer);
		if (!lexer->c
			&& (!ft_strncmp(value, ">", ft_strlen(value))
				|| !ft_strncmp(value, "<", ft_strlen(value))))
			return (init_token(TOKEN_ERROR, ERROR));
		return (init_token(TOKEN_INPUT, ft_strjoin(value, lexer_get_value(lexer))));
	}
	else if (lexer->c == '\'')
	{
		value = lexer_get_value_in_quote(lexer, '\'');
		if (lexer->c == '\'')
			lexer_skip_quote(lexer);
		if (!lexer->c
			&& (!ft_strncmp(value, ">", ft_strlen(value))
				|| !ft_strncmp(value, "<", ft_strlen(value))))
			return (init_token(TOKEN_ERROR, ERROR));
		return (init_token(TOKEN_INPUT, ft_strjoin(value, lexer_get_value(lexer))));
	}
	lexer_skip_whitespace(lexer);
	if (!lexer->c)
		return (init_token(TOKEN_ERROR, ERROR));
	return (init_token(TOKEN_INPUT, lexer_get_value(lexer)));
}
