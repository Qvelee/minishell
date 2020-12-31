# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/30 09:11:42 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
CC ?= gcc
CFLAGS ?= -c -g -MMD -Wall -Wextra -Werror
MAKEFLAGS ?= --no-print-directory
NAME = libft_readline.a
SRC = src/
OBJ = obj/
INCLUDES ?= -I../libft/includes -I../get_next_line/includes -I.. -I.
OBJ_FILES = \
			handle_keys.o\
			read_line.o\
			get_line.o\
			get_term_size.o\
			read_history.o\
			save_cursor.o\
			free_history.o\
			set_curpos_home.o\
			set_curpos_end.o\
			get_envp.o\
			get_cursor_start.o\
			cursor_inc.o\
			cursor_dec.o\
			read_line_utils.o\
			escape_seqs_utils.o\
			history.o\
			copy_paste.o\
			set_terminal_mode.o\
			remove_terminal_mode.o
UNAME = $(shell uname)
OBJ_OBJ_FILES = $(addprefix $(OBJ),$(OBJ_FILES))

all: $(OBJ) $(NAME)

$(OBJ):
	mkdir -p $(OBJ)

$(NAME): $(OBJ_OBJ_FILES)
	ar rcs $@ $?

$(OBJ)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -f $(NAME)
re:
	make fclean
	make all
bonus: all