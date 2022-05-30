/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:47:06 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/28 18:11:11 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	// if (!lexer)
	// 	return
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = lexer->contents[lexer->i];
	if (!lexer_check_quote(lexer))
	{
		printf("minishell: syntax error\n");
		return (NULL);
	}
	lexer->cmd_flag = 1;
	return (lexer);
}

int	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0'
		&& lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
		return (1);
	}
	return (0);
}

int	lexer_back(t_lexer *lexer)
{
	if (lexer->i > 0)
	{
		lexer->i--;
		lexer->c = lexer->contents[lexer->i];
		return (1);
	}
	return (0);
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

void	lexer_skip_quote(t_lexer *lexer)
{
	while (lexer->c == '"' || lexer->c == '\'')
		lexer_advance(lexer);
}
