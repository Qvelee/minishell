# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/11/16 18:15:26 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
CC = gcc
NAME = minishell
INCLUDES = . parsing executor libft/includes
LIB_DIR = parsing executor libft
LIB_NAMES = exec parsing ft
UNAME = $(shell uname)
CFLAGS = -g -Wall -Wextra -Werror
MAKEFLAGS = --no-print-directory
all: LIBS $(NAME)

LIBS :
	make -C executor
	make -C parsing
	make -C libft
$(NAME): main.h
	$(CC) $(CFLAGS) main.c $(addprefix -I,$(INCLUDES)) $(addprefix -L,$(LIB_DIR)) $(addprefix -l,$(LIB_NAMES)) -o $(NAME)

clean:
	make -C executor clean
	make -C libft clean
	make -C parsing clean

fclean:
	make -C executor fclean
	make -C libft fclean
	make -C parsing fclean
	rm -f $(NAME)
re:
	make fclean
	make WITH_BONUS=1 all
bonus:
	make WITH_BONUS=1 all