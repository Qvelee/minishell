# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/30 09:29:09 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
export CC CFLAGS MAKEFLAGS LDFLAGS INCLUDES
CC = gcc
CFLAGS = -c -g -MMD -Wall -Wextra -Werror
LDFLAGS = -g -Wall -Wextra -Werror
MAKEFLAGS = --no-print-directory
OBJ := main.o main_utils.o sygnals.o
OBJ := $(addprefix obj/,$(OBJ))
NAME = minishell
INCLUDES = -I$(PWD) -I$(PWD)/parsing -I$(PWD)/reading -I$(PWD)/executor -I$(PWD)/libft/includes -I$(PWD)/get_next_line/includes

LIB_DIR = parsing reading executor get_next_line libft
LIB_NAMES = exec parsing ft_readline get_next_line ft termcap
UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
	CFLAGS += -D LINUX=1
endif
ifdef WITH_BONUS
	make = make bonus
	CFLAGS += -D BONUS=1
	else
	make = make
endif

ifdef DEBUG
	CFLAGS += -pedantic -Wall -Wextra -std=c99 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector -Wno-pointer-arith -Wno-cast-qual -Wno-unused-result
endif

all: LIBS $(NAME)

LIBS :
	$(make) -C get_next_line
	$(make) -C parsing
	$(make) -C reading
	$(make) -C libft
	$(make) -C executor
	mkdir -p obj
$(NAME): $(OBJ) main.h executor/libexec.a parsing/libparsing.a libft/libft.a get_next_line/libget_next_line.a
	$(CC) $(LDLAGS) $(OBJ) $(INCLUDES) \
	$(addprefix -L,$(LIB_DIR)) $(addprefix -l,$(LIB_NAMES)) -o $(NAME)
obj/%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
clean:
	make -C get_next_line clean
	make -C executor clean
	make -C libft clean
	make -C reading clean
	make -C parsing clean
	rm -f *.o *.d
	rm -rf obj

debug :
	make WITH_BONUS=1 DEBUG=1 re

fclean:
	make -C get_next_line fclean
	make -C executor fclean
	make -C libft fclean
	make -C reading fclean
	make -C parsing fclean
	rm -f *.o *.d
	rm -rf obj
	rm -f $(NAME)
re: fclean all

bonus:
	make WITH_BONUS=1 all

rebonus: fclean
	make WITH_BONUS=1 all