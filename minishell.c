/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/11 15:30:40 by ael-bach         ###   ########.fr       */
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
	g_exitcode = 0;
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
		lexer = init_lexer(command, vr, g_exitcode);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		if (!parser)
			continue ;
		list = parser_parse(parser);
    	exec_pipe(list, vr);
		free(parser->token);
		free(parser);
		free(lexer->contents);
		free(lexer);
		free_list(list);
		// system("Leaks minishell");
	}
	return (0);
}