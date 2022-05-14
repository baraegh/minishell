/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:15:35 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/13 21:06:40 by eel-ghan         ###   ########.fr       */
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
}	t_lexer;

t_lexer	*init_lexer(char *contents);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer);
t_token	*lexer_collect_str(t_lexer *lexer, char c);
t_token	*lexer_collect_redirection(t_lexer *lexer, char c);

#endif