/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:48:38 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/14 19:39:06 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum {
		TOKEN_CMD,
		TOKEN_WORD,
		TOKEN_OUTPUT,
		TOKEN_INPUT,
		TOKEN_APPEND,
		TOKEN_HERE_DOC,
		TOKEN_PIPE,
		TOKEN_ERROR
	}		e_type;
	char	*value;
}	t_token;

t_token	*init_token(int type, char *value);

#endif