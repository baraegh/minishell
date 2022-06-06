/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bach <ael-bach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:17:00 by barae             #+#    #+#             */
/*   Updated: 2022/06/06 16:43:50 by ael-bach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

int	exitcode = 0;

void	print_t_cmd(t_cmd *list)
{
	int		j;
	t_file	*f_head;
	t_cmd	*head;

	printf("##########\n");
	head = list;
	while (head)
	{
		if (head!= NULL)
		{
			printf("cmd: %s\n", head->cmd[0]);
			j = 1;
			while (head->cmd[j])
			{
				printf("arg: %s\n", head->cmd[j]);
				j++;
			}
			f_head = head->file;
			while (f_head)
			{
				printf("red: %s, type: %d\n", f_head->file_name, f_head->type);
				f_head = f_head->next;
			}
		}
		printf("_________\n");
		head = head->next;
	}
	printf("##########\n");
}


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
	// vr->export = fill_export(env, vr);
	while (1)
	{
		command = readline("minishell 👾 $ ");
		if (command == NULL)
		{
			printf("exit");
			exit(0);
		}
		add_history(command);
		// if (!command)
		// 	continue ;
		lexer = init_lexer(command);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		// // if (!parser)
		// 	// return
		list = parser_parse(parser);
		// print_t_cmd(list);
		exec_pipe(list, vr);
		// free(lexer);
		// free(token);
		// free(parser->current_token);
		// free(parser->previous_token);
		// free(command);
		// system("Leaks minishell");
	}
	return (0);
}