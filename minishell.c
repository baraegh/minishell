/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:17:00 by barae             #+#    #+#             */
/*   Updated: 2022/05/19 18:04:08 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

int	main(int ac, char **av, char **env)
{
	char	*command = NULL;
	t_lexer	*lexer = NULL;
	t_token *token = NULL;

	(void) ac;
	(void) av;
	(void) env;
	while (1)
	{
		command = readline("minishell$ ");
		add_history(command);
		// if (!command)
		// 	continue ;
		lexer = init_lexer(command);
		if (!lexer)
		{
			printf("minishell: syntax error\n");
			continue ;
		}
		while ((token = lexer_get_next_token(lexer)) != NULL)
		{
			if (token->type == 7)
			{
				printf("minishell: %s\n",  token->value);
				break ;
			}
			printf("TOKEN(%d, %s)\n", token->type, token->value);
		}
		free(lexer);
		free(token);
		free(command);
	}
	return (0);
}