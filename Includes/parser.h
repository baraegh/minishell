/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:28:30 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 18:49:28 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*token;
}	t_parser;

t_parser	*init_parser(t_lexer *lexer);
t_cmd		*parser_parse(t_parser *parser);
void		parser_parse_cmd(t_parser *parser, t_cmd *head);
void		parser_parse_word(t_parser *parser, t_cmd *head, int *i);
void		parser_parse_redirection(t_parser *parser, t_cmd *head);
t_cmd		*parser_parse_pipe(t_parser *parser, t_cmd **head);
void		*parser_handle_error(t_parser *parser, t_cmd *head);
char		**add_arg_to_arr(char **arr, char *arg, int len);
void		free_list(t_cmd *list);
int			check_space(char *command);
void		*parser_parse_util(t_parser *parser, t_cmd *cmd_list);
t_token		*free_get_token(t_parser *parser);
void		parser_parse_util00(t_parser *parser, t_cmd *cmd_list, int *i);
void		parser_handle_here_dog(t_parser *parser, t_cmd *head);
int			parser_check(t_parser *parser);

#endif
