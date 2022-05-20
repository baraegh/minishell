/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:31:17 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/19 18:32:43 by eel-ghan         ###   ########.fr       */
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

int		lexer_check_quote(t_lexer *lexer)
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

	value = malloc(sizeof(char));
	// if (!value)
	// 	return
	value[0] = '\0';
	while (lexer->c != ' ' && lexer->c)
	{
		if (lexer->c == '"' || lexer->c == '\'' )
		{
			lexer_advance(lexer);
			continue ;
		}
		else if (lexer->c == '>' || lexer->c == '<')
			break ;
		s = lexer_get_char_as_str(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	// free(s);
	return (value);
}

char	*lexer_get_value_skip_quote(t_lexer *lexer, char c)
{
	char	*value;
	char	*s;

	value = malloc(sizeof(char));
	// if (!value)
	// 	return
	value[0] = '\0';
	while (lexer->c)
	{
		if (lexer->c == c)
		{
			lexer_advance(lexer);
			if (lexer->c == ' ')
				break ;
			continue ;
		}
		s = lexer_get_char_as_str(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	// free(s);
	return (value);
}

char	*lexer_get_value_in_quote(t_lexer *lexer, char c)
{
	char	*value;
	char	*s;

	lexer_skip_quote(lexer);
	value = malloc(sizeof(char));
	// if (!value)
	// 	return
	value[0] = '\0';
	while (lexer->c != c && lexer->c)
	{
		s = lexer_get_char_as_str(lexer);
		value = ft_strjoin(value, s);
		lexer_advance(lexer);
	}
	// free(s);
	return (value);
}