/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/14 15:12:40 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Includes/header.h"

void	handle_sigint(int sigint)
{
	(void) sigint;
	g_data.exitcode = 1;
	if (g_data.flag)
	{
		g_data.exitheredoc = 1; 
		printf("\n");
		close(0);
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
	g_data.fd  = dup(0);
	vr = fill_env(env);
	g_data.exitcode = 0;
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
		lexer = init_lexer(command, vr, g_data.exitcode);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		if (!parser)
			continue ;
		g_data.exitheredoc = 0;
		g_data.heredoc = 0;
		list = parser_parse(parser);
    	exec_pipe(list, vr);
		printf("file: %s\n", list->file->file_name);
		free(parser->token);
		free(parser);
		free(lexer->contents);
		free(lexer);
		free_list(list);
		// system("Leaks minishell");
	}
	return (0);
}