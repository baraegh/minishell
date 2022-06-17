/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:40:21 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 19:32:55 by eel-ghan         ###   ########.fr       */
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
		else if (handle_hd_error(parser, head))
			break ;
		else if (handle_rd_error(parser))
			return (parser_handle_error(parser, head));
		parser->token = free_get_token(parser);
	}
	return ("OK");
}

t_cmd	*parser_parse(t_parser *parser)
{
	t_cmd	*cmd_list;

	g_data.exitheredoc = 0;
	g_data.heredoc = 0;
	g_data.rd_error = 0;
	g_data.flag = 0;
	g_data.cd = 0;
	g_data.h_sig = 0;
	if (parser->token == NULL)
		return (NULL);
	cmd_list = init_struct_cmd();
	if (!cmd_list)
		return (NULL);
	if (!parser_parse_util(parser, cmd_list))
		return (NULL);
	return (cmd_list);
}
