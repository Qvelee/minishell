# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/30 08:04:02 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC ?= gcc
CFLAGS ?= -c -MMD -g -Wall -Wextra -Werror
MAKEFLAGS ?= --no-print-directory
NAME = libget_next_line.a
SRC = srcs/
OBJ = obj/
INCLUDES = includes
OBJ_FILES = get_next_line.o get_next_line_utils.o
D_FILES = $(OBJ_FILES:.o=.d)

all: $(OBJ) $(NAME)

$(OBJ):
	mkdir -p $(OBJ)

$(NAME): $(addprefix $(OBJ),$(OBJ_FILES))
	ar rcs $(NAME) $?

$(OBJ)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all
bonus: all
-include $(addprefix $(OBJ), $(D_FILES))
.PHONY: all clean fclean re so
