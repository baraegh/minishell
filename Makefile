# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barae <barae@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 03:45:02 by eel-ghan          #+#    #+#              #
#    Updated: 2022/06/13 19:50:14 by barae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LEX_DIR = srcs/Parsing/Lexer/

PARS_DIR = srcs/Parsing/Parser/

SRCS =	minishell.c ${LEX_DIR}lexer.c ${LEX_DIR}token.c ${LEX_DIR}lexer_utils00.c\
		${LEX_DIR}lexer_utils01.c ${LEX_DIR}redirection_utils.c ${LEX_DIR}env_utils.c\
		${LEX_DIR}dollar_utils00.c ${LEX_DIR}lexer_utils02.c ${LEX_DIR}get_value_utils.c\
		${LEX_DIR}dollar_utils.c ${LEX_DIR}skip_quote_utils.c ${PARS_DIR}parser.c ${PARS_DIR}struct_cmd.c\
		${PARS_DIR}linked_list_utils.c ${PARS_DIR}parser_utils00.c ${PARS_DIR}parser_utils01.c\
		./srcs/exec/srcs/exec.c\
		./srcs/exec/srcs/exec_part2.c\
		./srcs/exec/srcs/exec_utls.c\
		./srcs/exec/srcs/builtins.c\
		./srcs/exec/srcs/builtins_utls.c\
		./srcs/exec/srcs/export.c\
		./srcs/exec/srcs/unset.c\
		./srcs/exec/srcs/heredoc.c\
		./srcs/exec/srcs/utils.c\
		./srcs/exec/srcs/signals.c\
		

OBJS = ${SRCS:.c=.o}

OBJS = ${SRCS:.c=.o}

CC = @gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

RM = @rm -f

libft = srcs/Libft/libft.a

INCLUDE =	-lreadline -L /Users/eel-ghan/homebrew/opt/readline/lib\
			-I /Users/eel-ghan/homebrew/opt/readline/include

${NAME} : ${OBJS}
	@make -C srcs/Libft
#	${CC} ${libft} -o ${NAME} ${OBJS} ${INCLUDE}
	${CC} ${CFLAGS} ${SRCS} ${libft} -o ${NAME} ${INCLUDE}
	@tput setaf 2; echo "MINISHELL IS READY"

all : ${NAME}

clean :
	${RM} ${OBJS}
	@make clean -C srcs/Libft
	@tput setaf 1; echo "OBJECTS REMOVED"

fclean : clean
	${RM} ${NAME}
	${RM} ${libft}
	@tput setaf 1; echo "MINISHELL REMOVED"

re : fclean all

.phony: all clean fclean re
