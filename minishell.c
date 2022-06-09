/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:17:23 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/06/09 15:13:44 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

int	exitcode = 0;

int	main(int ac, char **av, char **env)
{
	char		*command = NULL;
	t_lexer		*lexer = NULL;
	t_parser	*parser = NULL;
	t_cmd		*list = NULL;
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
		lexer = init_lexer(command);
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
	}
	return (0);
}