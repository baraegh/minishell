/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:40:21 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/10 14:37:48 by eel-ghan         ###   ########.fr       */
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

t_cmd	*parser_parse(t_parser *parser)
{
	t_cmd	*cmd_list;
	t_cmd	*head;
	int		i;

	if (parser->token == NULL)
		return (NULL);
	cmd_list = init_struct_cmd();
	if(!cmd_list)
		return (NULL);
	head = cmd_list;
	i = 1;
	while (parser->token != NULL)
	{
		if (parser->token->type == TOKEN_CMD)
			parser_parse_cmd(parser, head);
		else if (parser->token->type == TOKEN_WORD)
			parser_parse_word(parser, head, &i);
		else if (parser->token->type == TOKEN_OUTPUT
			|| parser->token->type == TOKEN_INPUT
			|| parser->token->type == TOKEN_APPEND
			|| parser->token->type == TOKEN_HERE_DOC)
			parser_parse_redirection(parser, head);
		else if (parser->token->type == TOKEN_PIPE)
			t_cmd_add_back(&cmd_list, parser_parse_pipe(parser, &head));
		else if (parser->token->type == TOKEN_ERROR)
			return(parser_handle_error(parser, head));
		free(parser->token);
		parser->token = lexer_get_next_token(parser->lexer);
	}
	return (cmd_list);
}

void	parser_parse_cmd(t_parser *parser, t_cmd *head)
{
	head->cmd = add_arg_to_arr(head->cmd,
								parser->token->value,
								2);
}

void	parser_parse_word(t_parser *parser, t_cmd *head, int *i)
{
	head->cmd = add_arg_to_arr(head->cmd,
							parser->token->value,
							*(i) + 2);
	(*i)++;
}

void	parser_parse_redirection(t_parser *parser, t_cmd *head)
{
	if (!head->file)
	{
		head->file = init_file(parser->token->value,
								parser->token->type);
	}
	else
	{
		t_file_add_back(&head->file,
					init_file(parser->token->value,
								parser->token->type));
	}
}

t_cmd	*parser_parse_pipe(t_parser *parser, t_cmd **head)
{
	t_cmd	*cmd_new;

	(void) parser;
	cmd_new = init_struct_cmd();
	*head = cmd_new;
	return (cmd_new);
}

void	*parser_handle_error(t_parser *parser, t_cmd *head)
{
	printf("minishell: %s\n", parser->token->value);
	free_list(head);
	return (0);
}