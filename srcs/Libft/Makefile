# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 14:04:23 by eel-ghan          #+#    #+#              #
#    Updated: 2022/06/14 23:32:26 by eel-ghan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS	=	${SRCS:.c=.o}

BONUS_OBJS	=	${BONUS:.c=.o}

NAME	=	libft.a

rm		=	@rm -f

CFLAGS	=	-Wall -Wextra -Werror

CC		=	@gcc

AR		=	@ar -rc

${NAME}:	$(OBJS)
			${AR} $@ $^

all:	${NAME}

bonus:	$(BONUS_OBJS)
			${AR} ${NAME} $^

clean:
	${RM} ${OBJS}
	${RM} ${BONUS_OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all bonus

.PHONY:	all clean fclean re