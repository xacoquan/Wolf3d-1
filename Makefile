#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsisic <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/16 04:32:25 by bsisic            #+#    #+#              #
#    Updated: 2014/12/19 19:01:28 by bsisic           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME=		wolf3d

SRCS=		main.c		\
			init.c		\
			laby.c		\
			calc.c		\
			draw.c		\
			string.c	\
			handler.c	\
			minimap.c	\
			toggle.c

OBJS=		$(SRCS:.c=.o)

LIB=		-L/usr/X11/lib -lmlx -lXext -lX11 -lm

CFLAGS=		-Wall -Wextra -Werror -I/usr/X11/include/

CC=			gcc

RM=			rm -f

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(LIB)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
