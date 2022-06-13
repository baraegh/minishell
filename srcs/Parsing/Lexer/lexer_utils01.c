/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barae <barae@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:32 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/13 19:53:04 by barae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	lexer_find_pair(char *s, char c, int *i)
{
	*i += 1;
	while (s[*i])
	{
		if (s[*i] == c)
			return (1);
		*i += 1;
	}
	return (0);
}

int	lexer_check_quote(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->contents[i])
	{
		if (lexer->contents[i] == '"')
		{
			if (!lexer_find_pair(lexer->contents, '"', &i))
				return (0);
		}
		else if (lexer->contents[i] == '\'')
		{
			if (!lexer_find_pair(lexer->contents, '\'', &i))
				return (0);
		}
		i++;
	}
	return (1);
}

char	*lexer_get_value(t_lexer *lexer)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	if (!value)
		return (NULL);
	s = ft_calloc(1, sizeof(char));
	if (!s)
		return (NULL);
	value = get_value_util01(lexer, value, s);
	free(s);
	return (value);
}

char	*lexer_get_value_skip_quote(t_lexer *lexer, char c)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	if (!value)
		return (NULL);
	s = ft_calloc(1, sizeof(char));
	if (!s)
		return (NULL);
	lexer_advance(lexer);
	value = skip_quote(lexer, value, s, c);
	free(s);
	return (value);
}

char	*lexer_get_value_in_quote(t_lexer *lexer, char c)
{
	char	*value;
	char	*s;

	lexer_advance(lexer);
	if (lexer->c == c)
		return (ft_strdup(""));
	value = ft_calloc(1, sizeof(char));
	if (!value)
		return (NULL);
	while (lexer->c != c)
	{
		s = lexer_get_char_as_str(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '"')
		lexer_advance(lexer);
	return (value);
}
