/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:17:00 by barae             #+#    #+#             */
/*   Updated: 2022/06/06 14:39:30 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/header.h"

void	print_t_cmd(t_cmd *list)
{
	int		j;
	t_file	*f_head;
	t_cmd	*head;

	printf("##########\n");
	head = list;
	while (head)
	{
		if (head != NULL)
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

	(void) ac;
	(void) av;
	(void) env;
	while (1)
	{
		command = readline("minishell 👻 $ ");
		if (!command || !*command)
			continue ;
		add_history(command);
		lexer = init_lexer(command);
		if (!lexer)
			continue ;
		parser = init_parser(lexer);
		// // if (!parser)
		// 	// return
		list = parser_parse(parser);
		print_t_cmd(list);
		free(command);
		free(lexer);
		free(parser->current_token);
		free(parser->previous_token);
		free(parser);
		// system("Leaks minishell");
	}
	return (0);
}