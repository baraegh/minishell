/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:17:00 by barae             #+#    #+#             */
/*   Updated: 2022/05/14 16:36:28 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

int	main(void)
{
	char	*command = NULL;
	t_lexer	*lexer = NULL;
	t_token *token = NULL;

	while (1)
	{
		command = readline("minishell$ ");
		// if (!command)
		// 	continue ;
		lexer = init_lexer(command);
		while ((token = lexer_get_next_token(lexer)) != NULL)
			printf("TOKEN(%d, %s)\n", token->type, token->value);
		free(lexer);
		free(token);
		free(command);
	}
	return (0);
}