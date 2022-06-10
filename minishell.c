/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/10 14:37:30 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

int	exitcode = 0;

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
	// vr->export = fill_export(vr->env, vr);
		command = readline("minishell 👻 $ ");
		if (!command || !*command
			|| !check_space(command))
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
		// exec_pipe(list, vr);
		free_list(list);
	}
	return (0);
}