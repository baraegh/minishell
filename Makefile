# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 03:45:02 by barae             #+#    #+#              #
#    Updated: 2022/05/20 13:28:42 by eel-ghan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LEX_DIR = srcs/Parsing/Lexer/

SRCS =	minishell.c ${LEX_DIR}lexer.c ${LEX_DIR}token.c ${LEX_DIR}lexer_utils00.c\
		${LEX_DIR}lexer_utils01.c ${LEX_DIR}lexer_utils02.c\

OBJS = ${SRCS:.c=.o}

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

RM = @rm -f

libft = srcs/Libft/libft.a

INCLUDE = -lreadline

${NAME} : ${OBJS}
	@make -C srcs/Libft
	${CC} ${libft} -o ${NAME} ${OBJS} ${INCLUDE}
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
