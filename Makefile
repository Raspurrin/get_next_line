# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/08 21:37:57 by mialbert          #+#    #+#              #
#    Updated: 2021/12/14 19:55:58 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = get_next_line.a
SRCS = get_next_line.c get_next_line_utils.c
OBJS = $(SRCS.c=.o)

all : $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS)

$(NAME) : $(OBJS)
	ar rcs $(OBJS) $(NAME)

test : 
	$(CC) $(CFLAGS) $(SRCS) && ./a.out

clean: 
	rm -f $(OBJS)

fclean : clean
	rm -f (NAME)

re : fclean all