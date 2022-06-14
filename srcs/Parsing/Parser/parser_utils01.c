/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:00:18 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/14 21:50:50 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/header.h"

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
				parser->token->e_type);
	}
	else
	{
		t_file_add_back(&head->file,
			init_file(parser->token->value,
				parser->token->e_type));
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
