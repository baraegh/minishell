/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:40:21 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/31 13:51:12 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	// if (!parser)
	// 	return();
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(parser->lexer);
	parser->previous_token = NULL;
	return (parser);
}

t_cmd	*parser_parse(t_parser *parser)
{
	t_cmd	*cmd_list;
	t_cmd	*head;
	int		i;

	if (parser->current_token == NULL)
		return (NULL);
	cmd_list = init_struct_cmd();
	// if(!cmd_list)
		// return
	head = cmd_list;
	i = 1;
	while (parser->current_token != NULL)
	{
		if (parser->current_token->type == TOKEN_CMD)
			parser_parse_cmd(parser, head);
		else if (parser->current_token->type == TOKEN_WORD)
			parser_parse_word(parser, head, &i);
		else if (parser->current_token->type == TOKEN_OUTPUT
			|| parser->current_token->type == TOKEN_INPUT
			|| parser->current_token->type == TOKEN_APPEND
			|| parser->current_token->type == TOKEN_HERE_DOC)
			parser_parse_redirection(parser, head);
		else if (parser->current_token->type == TOKEN_PIPE)
			t_cmd_add_back(&cmd_list, parser_parse_pipe(parser, &head));
		else if (parser->current_token->type == TOKEN_ERROR)
			return(parser_handle_error(parser, head));
		parser->previous_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
	}
	return (cmd_list);
}

void	parser_parse_cmd(t_parser *parser, t_cmd *head)
{
	head->cmd = add_arg_to_arr(head->cmd,
								parser->current_token->value,
								2);
}

void	parser_parse_word(t_parser *parser, t_cmd *head, int *i)
{
	head->cmd = add_arg_to_arr(head->cmd,
							parser->current_token->value,
							*(i) + 2);
	(*i)++;
}

void	parser_parse_redirection(t_parser *parser, t_cmd *head)
{
	if (!head->file)
	{
		head->file = init_file(parser->current_token->value,
								parser->current_token->type);
	}
	else
	{
		t_file_add_back(&head->file,
					init_file(parser->current_token->value,
								parser->current_token->type));
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

//TODO: free the head's struct if(head != NULL)
void	*parser_handle_error(t_parser *parser, t_cmd *head)
{
	(void) head;
	printf("minishell: %s\n", parser->current_token->value);
	return (0);
}