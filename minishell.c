/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/15 02:39:23 by eel-ghan         ###   ########.fr       */
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
		g_data.flag = 0;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	free_util(t_parser *parser, t_lexer *lexer,
	t_cmd *list)
{
	free(parser->token);
	free(parser);
	free(lexer->contents);
	free(lexer);
	free_list(list);
}

t_lexer	*get_lexer(char *command, t_vr *vr)
{
	t_lexer		*lexer;

	g_data.here_doc_flag = 0;
	if (!command)
	{
		free(command);
		exit(130);
	}
	if (!*command || !check_space(command))
	{
		free(command);
		return (NULL);
	}
	add_history(command);
	lexer = init_lexer(command, vr, g_data.exitcode);
	if (!lexer)
		return (NULL);
	return (lexer);
}

t_vr	*init_vr(char **env)
{
	g_data.fd = dup(0);
	g_data.exitcode = 0;
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (fill_env(env));
}

int	main(int ac, char **av, char **env)
{
	char		*command;
	t_parser	*parser;
	t_lexer		*lexer;
	t_cmd		*list;
	t_vr		*vr;

	(void) ac;
	(void) av;
	vr = init_vr(env);
	while (1)
	{
		command = readline("minishell $ ");
		lexer = get_lexer(command, vr);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		if (!parser)
			continue ;
		list = parser_parse(parser);
		exec_pipe(list, vr);
		free_util(parser, lexer, list);
	}
	return (0);
}
