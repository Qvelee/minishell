# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/28 15:00:38 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
CC = gcc
NAME = libft_readline.a
SRC = src/
OBJ = obj/
INCLUDES = includes
OBJ_FILES = \
handle_escape_sequence.o\
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
copy_paste.o
UNAME = $(shell uname)
REG_OBJ_FILES = $(addprefix $(OBJ),$(OBJ_FILES))
BONUS_OBJ_FILES = $(addprefix $(OBJ),$(BONUS_FILES))
CFLAGS = -g -Wall -Wextra -Werror
MAKEFLAGS = --no-print-directory
ifdef WITH_BONUS
CFLAGS += -D BONUS=1
OBJ_OBJ_FILES = $(REG_OBJ_FILES) $(BONUS_OBJ_FILES)
else
OBJ_OBJ_FILES = $(REG_OBJ_FILES)
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