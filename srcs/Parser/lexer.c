/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:47:06 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/14 16:39:17 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/header.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	// if (!lexer)
	// 	return
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = lexer->contents[lexer->i];
	lexer->cmd_flag = 1;
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0'
		&& lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0'
		&& lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		if (lexer->c == '"')
			return (lexer_collect_str(lexer, '"'));
		if (lexer->c == '>')
			return (lexer_collect_redirection(lexer, '>'));
		if (lexer->c == '<')
			return (lexer_collect_redirection(lexer, '<'));
		return (lexer_collect_str(lexer, ' '));
	}
	return (NULL);
}

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

t_token	*lexer_collect_str(t_lexer *lexer, char c)
{
	char	*value;
	char	*s;

	if (c == '"')
		lexer_advance(lexer);
	if (lexer->c == '\0')
		return (NULL);
	value = malloc(sizeof(char));
	// if (!value)
	// 	return
	value[0] = '\0';
	while (lexer->c != c && lexer->c != '\0')
	{
		s = lexer_get_char_as_str(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	if (lexer->cmd_flag)
	{
		lexer->cmd_flag = 0;
		return (init_token(TOKEN_CMD, value));
	}
	return (init_token(TOKEN_WORD, value));
}

t_token	*lexer_collect_redirection(t_lexer *lexer, char c)
{
	char	*value;
	char	*s;
	int		i;

	if (lexer->i + 1 < ft_strlen(lexer->contents))
	{
		if (lexer->contents[lexer->i + 1] == c)
		{
			value = malloc(sizeof(char));
			// if (!value)
			// 	return
			value[0] = '\0';
			i = 0;
			while (i < 2)
			{
				s = lexer_get_char_as_str(lexer);
				value = ft_strjoin(value, s);
				lexer_advance(lexer);
				i++;
			}
			return (init_token(TOKEN_REDIRECTION, value));
		}
	}
	s = lexer_get_char_as_str(lexer);
	lexer_advance(lexer);
	return (init_token(TOKEN_REDIRECTION, s));
}
