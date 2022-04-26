# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barae <barae@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 03:45:02 by barae             #+#    #+#              #
#    Updated: 2022/04/26 00:33:25 by barae            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c

CC = @gcc

CFLAGS = -Wall -Wextra -Werror

RM = @rm -f

libft = srcs/Libft/libft.a

${NAME} :
	@make -C srcs/Libft
	${CC} ${CFLAGS} ${SRCS} ${libft} -o ${NAME}
	@tput setaf 2; echo "MINISHELL IS READY"

all : ${NAME}

clean :
	${RM} ${NAME}
	@make clean -C srcs/Libft
	@tput setaf 1; echo "OBJECTS REMOVED"

fclean : clean
	${RM} ${NAME}
	${RM} ${libft}
	@tput setaf 1; echo "MINISHELL REMOVED"

re : fclean all

.phony: all clean fclean re
