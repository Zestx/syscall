# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 17:44:40 by qbackaer          #+#    #+#              #
#    Updated: 2020/01/28 18:51:04 by qbackaer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = minishell
INCLUDES = minishell.h
SRCS = pipe7-rev.c 
OBJS = pipe7-rev.o 

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $^ -I. ./libft/libft.a -o pipeline
	rm -rf *.o

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I. -c $^

clean:
	rm -rf *.o
	make fclean -C ./libft

fclean: clean
	rm -rf pl

re: fclean all

.PHONY: re fclean clean all
