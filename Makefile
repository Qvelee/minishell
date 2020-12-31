# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 20:40:17 by sgertrud          #+#    #+#              #
#    Updated: 2020/12/31 11:01:18 by sgertrud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re main bonus
export CC CFLAGS MAKEFLAGS LDFLAGS INCLUDES
CC 			= gcc
CFLAGS 		= -c -MMD -Wall -Wextra -Werror
LDFLAGS 	= -Wall -Wextra -Werror
DFLAGS 		= -g
ASFLAGS 	= -fsanitize=address
HFLAGS		= '-pedantic -std=c99 -O2 -Wshadow -Wformat=2 -Wfloat-equal\
	-Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align\
	-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2\
	-fsanitize=undefined -fno-sanitize-recover -fstack-protector\
	-Wno-pointer-arith -Wno-cast-qual -Wno-unused-result'
MAKEFLAGS	= --no-print-directory
OBJ 		:= main.o main_utils.o sygnals.o
OBJ 		:= $(addprefix obj/,$(OBJ))
NAME 		= minishell
INCLUDES 	= -I$(PWD) -I$(PWD)/parsing -I$(PWD)/reading -I$(PWD)/executor\
			-I$(PWD)/libft/includes -I$(PWD)/get_next_line/includes
LIB_DIR 	= parsing reading executor get_next_line libft
VPATH 		= parsing reading executor get_next_line libft
LIB_NAMES 	= exec parsing ft_readline get_next_line ft termcap
CLIBS		= $(addprefix lib, $(LIB_NAMES))
UNAME 		= $(shell uname)

ifeq ($(UNAME), Linux)
	CFLAGS += -D LINUX=1
endif
ifdef WITH_BONUS
	make = make bonus
	CFLAGS += -D BONUS=1
	else
	make = make
endif

all: LIBS $(NAME)

LIBS : P_OBJ
	$(make) -C get_next_line
	$(make) -C parsing
	$(make) -C reading
	$(make) -C libft
	$(make) -C executor
P_OBJ:
	mkdir -p obj

$(NAME): $(OBJ) executor/libexec.a parsing/libparsing.a libft/libft.a get_next_line/libget_next_line.a
	$(CC) $(LDFLAGS) $(OBJ) $(INCLUDES) \
	$(addprefix -L,$(LIB_DIR)) $(addprefix -l,$(LIB_NAMES)) -o $(NAME)
obj/%.o : %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

bonus:
	make WITH_BONUS=1 all
debug :
	make bonus CFLAGS+=$(DFLAGS) LDFLAGS+=$(DFLAGS)
debugas :
	make debug CFLAGS+=$(ASFLAGS) LDFLAGS+=$(ASFLAGS)
debugh :
	make debugas CFLAGS+=$(HFLAGS) LDFLAGS+=$(HFLAGS)

clean:
	make -C get_next_line clean
	make -C executor clean
	make -C libft clean
	make -C reading clean
	make -C parsing clean
	rm -f *.o *.d
	rm -rf obj

fclean:
	make -C get_next_line fclean
	make -C executor fclean
	make -C libft fclean
	make -C reading fclean
	make -C parsing fclean
	rm -f *.o *.d
	rm -rf obj
	rm -f $(NAME)
%re:
	make fclean
	make $(patsubst %re, %, $@)
re:
	make fclean
	make
