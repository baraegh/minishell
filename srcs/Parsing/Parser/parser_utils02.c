/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:46:40 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 19:47:55 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

int	parser_check(t_parser *parser)
{
	if (parser->token->e_type == TOKEN_OUTPUT
		|| parser->token->e_type == TOKEN_INPUT
		|| parser->token->e_type == TOKEN_APPEND
		|| parser->token->e_type == TOKEN_HERE_DOC)
		return (1);
	return (0);
}

void	parser_handle_here_dog(t_parser *parser, t_cmd *head)
{
	printf("minishell: %s\n", parser->token->value);
	if (parser->token->e_type != TOKEN_RD_ERROR)
		parser_parse_redirection(parser, head);
	g_data.here_doc_flag = 0;
	g_data.rd_error = 1;
}

int	handle_hd_error(t_parser *parser, t_cmd *head)
{
	g_data.exitcode = 258;
	if (parser->token->e_type == TOKEN_RD_ERROR
		&& g_data.here_doc_flag == 1)
	{
		parser_handle_here_dog(parser, head);
		return (1);
	}
	return (0);
}

int	handle_rd_error(t_parser *parser)
{
	g_data.exitcode = 258;
	if (parser->token->e_type == TOKEN_RD_ERROR
		&& g_data.here_doc_flag == 0)
		return (1);
	return (0);
}

t_token	*free_get_token(t_parser *parser)
{
	free(parser->token);
	return (lexer_get_next_token(parser->lexer));
}
