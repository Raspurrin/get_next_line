# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/08 21:37:57 by mialbert          #+#    #+#              #
#    Updated: 2021/12/27 20:55:03 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
NAME = get_next_line.a
SRCS = get_next_line.c get_next_line_utils.c
BONUS_SRCS = $(shell find . -iname "*_bonus.c")
OBJS = $(SRCS.c=.o)

all : $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS)

$(NAME) : $(OBJS)
	ar rcs $(OBJS) $(NAME)

bonus :
	$(CC) -std=c11 $(CFLAGS) -ggdb3 $(BONUS_SRCS) && ./a.out

test : 
	$(CC) -std=c11 $(CFLAGS) -ggdb3 $(SRCS) && ./a.out

unittest:
	cd gnlTester && make && cd ..

valgrind: test
	@echo ""
	@valgrind --leak-check=full ./a.out

clean: 
	rm -f $(OBJS)

fclean : clean
	rm -f (NAME)

re : fclean all 

# .PHONY clean fclean re test valgrind all