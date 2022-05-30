/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:28:30 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/30 18:22:10 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_token;
	t_token	*previous_token;
}	t_parser;

t_parser	*init_parser(t_lexer *lexer);
t_cmd		*parser_parse(t_parser *parser);
void		parser_parse_cmd(t_parser *parser, t_cmd *head);
void		parser_parse_word(t_parser *parser, t_cmd *head, int *i);
void		parser_parse_redirection(t_parser *parser, t_cmd *head);
t_cmd		*parser_parse_pipe(t_parser *parser, t_cmd **head);
void		*parser_handle_error(t_parser *parser, t_cmd *head);
char		**add_arg_to_arr(char **arr, char *arg, int len);

#endif
