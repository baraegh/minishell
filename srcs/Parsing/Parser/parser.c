/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:40:21 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/14 21:50:35 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->lexer = lexer;
	parser->token = lexer_get_next_token(parser->lexer);
	return (parser);
}

int	parser_check(t_parser *parser)
{
	if (parser->token->e_type == TOKEN_OUTPUT
		|| parser->token->e_type == TOKEN_INPUT
		|| parser->token->e_type == TOKEN_APPEND
		|| parser->token->e_type == TOKEN_HERE_DOC)
		return (1);
	return (0);
}

void	*parser_parse_util(t_parser *parser, t_cmd *cmd_list)
{
	int		i;
	t_cmd	*head;

	i = 1;
	head = cmd_list;
	while (parser->token != NULL)
	{
		if (parser->token->e_type == TOKEN_CMD)
			parser_parse_cmd(parser, head);
		else if (parser->token->e_type == TOKEN_WORD)
			parser_parse_word(parser, head, &i);
		else if (parser_check(parser))
			parser_parse_redirection(parser, head);
		else if (parser->token->e_type == TOKEN_PIPE)
			t_cmd_add_back(&cmd_list, parser_parse_pipe(parser, &head));
		else if (parser->token->e_type == TOKEN_ERROR)
			return (parser_handle_error(parser, head));
		free(parser->token);
		parser->token = lexer_get_next_token(parser->lexer);
	}
	return ("OK");
}

t_cmd	*parser_parse(t_parser *parser)
{
	t_cmd	*cmd_list;

	if (parser->token == NULL)
		return (NULL);
	cmd_list = init_struct_cmd();
	if (!cmd_list)
		return (NULL);
	if (!parser_parse_util(parser, cmd_list))
		return (NULL);
	return (cmd_list);
}
