/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/13 11:51:01 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Includes/header.h"

void	handle_sigint(int sigint)
{
	(void) sigint;
	g_exitcode = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


int	main(int ac, char **av, char **env)
{
	char		*command;
	t_lexer		*lexer;
	t_parser	*parser;
	t_cmd		*list;
	t_vr		*vr;

	(void) ac;
	(void) av;
	g_exitcode = 0;
	vr = fill_env(env);
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
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