/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/11 14:58:56 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_lexer		*lexer;
	t_parser	*parser;
	t_cmd		*list;
	t_vr		*vr;

	(void) ac;
	(void) av;	
	vr = fill_env(env);
	while (1)
	{
		command = readline("minishell $ ");
		if (!command)
		{
			free(command);
			exit (0) ;
		}
		if (!*command || !check_space(command))
		{
			free(command);
			continue ;
		}
		add_history(command);
		lexer = init_lexer(command, vr);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		if (!parser)
			continue ;
		list = parser_parse(parser);
		free(parser->token);
		free(parser);
		free(lexer->contents);
		free(lexer);
    	exec_pipe(list, vr);
		free_list(list);
		// system("Leaks minishell");
	}
	return (0);
}