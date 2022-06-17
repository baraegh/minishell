/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:47:06 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 02:07:35 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_lexer	*init_lexer(char *contents, t_vr *vr, int exit_code)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = lexer->contents[lexer->i];
	if (!lexer_check_quote(lexer))
	{
		free(lexer);
		free(lexer->contents);
		g_data.exitcode = 258;
		printf("minishell: syntax error, unclosed quotes\n");
		return (NULL);
	}
	lexer->cmd_flag = 1;
	lexer->vr = vr;
	lexer->exit_code = exit_code;
	lexer->flag = 0;
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
