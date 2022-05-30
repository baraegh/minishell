/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:48:38 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/05/30 14:22:00 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
	enum token
	{
		TOKEN_CMD,
		TOKEN_WORD,
		TOKEN_OUTPUT,
		TOKEN_INPUT,
		TOKEN_APPEND,
		TOKEN_HERE_DOC,
		TOKEN_PIPE,
		TOKEN_ERROR,
	}	type;
	char	*value;
}	t_token;

t_token	*init_token(int type, char *value);

#endif