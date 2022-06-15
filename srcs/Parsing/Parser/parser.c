/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:40:21 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 18:50:26 by eel-ghan         ###   ########.fr       */
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
		if (parser->token->e_type != TOKEN_ERROR
			&& parser->token->e_type != TOKEN_RD_ERROR)
			parser_parse_util00(parser, cmd_list, &i);
		else if (parser->token->e_type == TOKEN_ERROR)
			return (parser_handle_error(parser, head));
		else if (parser->token->e_type == TOKEN_RD_ERROR
			&& g_data.here_doc_flag == 1)
		{
			parser_handle_here_dog(parser, head);
			break ;
		}
		else if (parser->token->e_type == TOKEN_RD_ERROR
			&& g_data.here_doc_flag == 0)
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
	if (parser->token == NULL)
		return (NULL);
	cmd_list = init_struct_cmd();
	if (!cmd_list)
		return (NULL);
	if (!parser_parse_util(parser, cmd_list))
		return (NULL);
	return (cmd_list);
}
