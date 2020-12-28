# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/28 19:25:24 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
CC = gcc
NAME = libparsing.a
SRC = src/
OBJ = obj/
INCLUDES = includes
OBJ_FILES = \
check_end.o\
parse_command.o\
check_validity.o\
parse_utils.o \
set_terminal_mode.o
UNAME = $(shell uname)
OBJ_OBJ_FILES = $(addprefix $(OBJ),$(OBJ_FILES))
CFLAGS = -g -Wall -Wextra -Werror
MAKEFLAGS = --no-print-directory
ifdef WITH_BONUS
CFLAGS += -D BONUS=1
endif

all: $(OBJ) $(NAME)

$(OBJ):
	mkdir -p $(OBJ)

$(NAME): $(OBJ_OBJ_FILES)
	ar rcs $@ $?

$(OBJ)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -g -fPIE -c -I.. -Iincludes -I. -I../libft/includes -I../source $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -f write.txt
	rm -f $(NAME)
	rm -f ./a.out
re:
	make fclean
	make WITH_BONUS=1 all
bonus:
	make WITH_BONUS=1 all