/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:38:05 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/09 14:54:21 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

char	*get_str(t_lexer *lexer)
{
	char	*s;

	s = ft_calloc(1, sizeof(char));
	if (!s)
		return (NULL);
	while (lexer->c != ' ' && lexer->c)
	{
		if ((lexer->c < 'a' || lexer->c > 'z')
			&& (lexer->c < 'A' || lexer->c > 'Z')
			&& (lexer->c < '0' || lexer->c > '9')
			&& lexer->c != '_')
			break ;
		if (lexer->c == '>' || lexer->c == '<'
			|| lexer->c == '|')
			break ;
		s = ft_strjoin(s, lexer_get_char_as_str(lexer));
		lexer_advance(lexer);
	}
	return (s);
}

char	*get_str2(t_lexer *lexer)
{
	char	*s;

	lexer_back(lexer);
	s = ft_calloc(1, sizeof(char));
	if (!s)
		return (NULL);
	s = ft_strjoin(s, lexer_get_char_as_str(lexer));
	if (!s)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != ' ' && lexer->c)
	{
		if ((lexer->c < 'a' || lexer->c > 'z')
			&& (lexer->c < 'A' || lexer->c > 'Z')
			&& (lexer->c < '0' || lexer->c > '9')
			&& lexer->c != '_' && lexer->c != '$')
			break ;
		if (lexer->c == '>' || lexer->c == '<'
			|| lexer->c == '|')
			break ;
		s = ft_strjoin(s, lexer_get_char_as_str(lexer));
		if (!s)
			return (NULL);
		lexer_advance(lexer);
		if (lexer->c == '$')
			break ;
	}
	return (s);
}

char	*handle_dollar(t_lexer *lexer)
{
	char	*s = NULL;
	char	*value;

	if (lexer_advance(lexer)
		&& (lexer->c == '"' || lexer->c == '\''))
	{
		lexer_back(lexer);
		return (NULL);
	}
	if (!lexer->c)
		return (ft_strdup("$"));
	if (lexer->c == '?')
	{
		lexer_advance(lexer);
		return(ft_strdup("$?"));
	}
	if ((lexer->c < 'a' || lexer->c > 'z')
		&& (lexer->c < 'A' || lexer->c > 'Z')
		&& (lexer->c < '0' || lexer->c > '9')
		&& lexer->c != '_')
		return(get_str2(lexer));
	s = get_str(lexer);
	value = ft_strdup(getenv(s));
	free(s);
	if (!value)
	{
		value = ft_calloc(1, sizeof(char));
		if (!value)
			return (NULL);
	}
	return (value);
}