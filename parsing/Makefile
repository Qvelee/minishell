# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/30 08:48:37 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
CC ?= gcc
NAME = libparsing.a
SRC = src/
OBJ = obj/
INCLUDES ?= -I../libft/includes -I../get_next_line/includes -I.. -I.
OBJ_FILES = \
			check_end.o\
			parse_command.o\
			check_validity.o\
			parse_utils.o
UNAME = $(shell uname)
OBJ_OBJ_FILES = $(addprefix $(OBJ),$(OBJ_FILES))
CFLAGS ?= -g -Wall -Wextra -Werror
MAKEFLAGS ?= --no-print-directory

all: $(OBJ) $(NAME)

$(OBJ):
	mkdir -p $(OBJ)

$(NAME): $(OBJ_OBJ_FILES)
	ar rcs $@ $?

$(OBJ)%.o: $(SRC)%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -f write.txt
	rm -f $(NAME)
	rm -f ./a.out

re: fclean all

bonus: all