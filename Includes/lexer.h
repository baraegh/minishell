/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:15:35 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/20 13:29:20 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer
{
	char	c;
	int		i;
	char	*contents;
	int		cmd_flag;
	int		pipe_flag;
}	t_lexer;

t_lexer	*init_lexer(char *contents);
int		lexer_advance(t_lexer *lexer);
int		lexer_back(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
int		lexer_check_quote(t_lexer *lexer);
int		lexer_find_pair(char *s, char c, int *i);
char	*lexer_get_char_as_str(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*lexer_collect_str(t_lexer *lexer);
t_token	*lexer_collect_pipe(t_lexer *lexer);
t_token	*lexer_collect_out_red(t_lexer *lexer);
t_token	*lexer_collect_in_red(t_lexer *lexer);
char	*lexer_get_value(t_lexer *lexer);
void	lexer_skip_quote(t_lexer *lexer);
char	*lexer_get_value_skip_quote(t_lexer *lexer, char c);
char	*lexer_get_value_in_quote(t_lexer *lexer, char c);

#endif