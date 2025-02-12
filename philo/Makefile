# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nosman <nosman@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/06 07:31:41 by nosman            #+#    #+#              #
#    Updated: 2024/07/10 07:28:06 by nosman           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	philo
CC 		=	cc
CFLAGS	=	-Wall -Wextra -Werror -pthread
SRCS	= 	philo.c \
			utils.c \
			parsing.c  \
			initialization.c \
			routine.c \
			processes.c \
			monitoring.c

OBJS 	=	$(SRCS:.c=.o)

REMOVE	=	rm -rf

all:		$(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
			${REMOVE} ${OBJS}

fclean:		clean
			${REMOVE} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
