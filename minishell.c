/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/09 14:56:33 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Includes/header.h"

int	main(int ac, char **av, char **env)
{
	char		*command = NULL;
	t_lexer		*lexer = NULL;
	t_parser	*parser = NULL;
	t_cmd		*list = NULL;

	(void) ac;
	(void) av;
	(void) env;
	while (1)
	{
		command = readline("minishell 👻 $ ");
		if (!command || !*command
			|| !check_space(command))
		{
			free(command);
			continue ;
		}
		add_history(command);
		lexer = init_lexer(command);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		if (!parser)
			continue ;
		list = parser_parse(parser);
		print_t_cmd(list);
		free(parser->token);
		free(parser);
		free(lexer->contents);
		free(lexer);
		free_list(list);
	}
	return (0);
}