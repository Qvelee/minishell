# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/26 14:14:19 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
CC = gcc
OBJ = main.o main_utils.o sygnals.o
NAME = minishell
INCLUDES = . parsing executor libft/includes
LIB_DIR = parsing executor get_next_line libft
LIB_NAMES = exec parsing get_next_line ft tinfo
UNAME = $(shell uname)
CFLAGS = -g -Wall -Wextra -Werror
MAKEFLAGS = --no-print-directory
all: LIBS $(NAME)

LIBS :
	make -C get_next_line
	make -C executor
	make -C parsing
	make -C libft
$(NAME): $(OBJ) main.h executor/libexec.a parsing/libparsing.a libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(addprefix -I,$(INCLUDES)) $(addprefix -L,$(LIB_DIR)) $(addprefix -l,$(LIB_NAMES)) -o $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -c $(addprefix -I,$(INCLUDES)) $< -o $@
clean:
	make -C get_next_line clean
	make -C executor clean
	make -C libft clean
	make -C parsing clean
	rm -f *.o

fclean:
	make -C get_next_line fclean
	make -C executor fclean
	make -C libft fclean
	make -C parsing fclean
	rm -f *.o
	rm -f $(NAME)
re:
	make fclean
	make WITH_BONUS=1 all
bonus:
	make WITH_BONUS=1 all