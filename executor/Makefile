# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 14:15:44 by nelisabe          #+#    #+#              #
#    Updated: 2020/11/19 15:19:56 by nelisabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				libexec.a

COMP =				clang -g

FLAGS =				#-Wall -Wextra -Werror

MAIN_HEADER =		./executor_public.h

EXEC_HEADER = 		./executor.h

#SRC DIRS

MAIN_SRC_DIR =		./
EXEC_SRC_DIR =		./
BTIN_SRC_DIR =		./built-ins/
ENVP_SRC_DIR =		./envp/

#SRC

MAIN_SRC =			exit_minishell.c

EXEC_SRC =			do_command.c \
					commands.c

BTIN_SRC =			mini_echo.c \
					mini_pwd.c \
					mini_cd.c \
					mini_export.c \
					mini_export_2.c \
					mini_unset.c \
					mini_exit.c \
					mini_env.c

ENVP_SRC =			envp_treatment_1.c \
					envp_treatment_2.c \
					envp_lst_treatment_utils_1.c \
					envp_lst_treatment_utils_2.c

#OBJ DIRS

MAIN_OBJ_DIR =		./temp/
EXEC_OBJ_DIR =		./temp/executor/
BTIN_OBJ_DIR =		./temp/executor/built-ins/
ENVP_OBJ_DIR =		./temp/executor/envp/

#OBJ

MAIN_OBJ =				$(addprefix $(MAIN_OBJ_DIR), $(MAIN_SRC:.c=.o))
EXEC_OBJ =				$(addprefix $(EXEC_OBJ_DIR), $(EXEC_SRC:.c=.o))
BTIN_OBJ =				$(addprefix $(BTIN_OBJ_DIR), $(BTIN_SRC:.c=.o))
ENVP_OBJ =				$(addprefix $(ENVP_OBJ_DIR), $(ENVP_SRC:.c=.o))


D_FILES = $(patsubst %.o, %.d, $(MAIN_OBJ)) $(patsubst %.o, %.d, $(EXEC_OBJ)) $(patsubst %.o, %.d, $(BTIN_OBJ)) $(patsubst %.o, %.d, $(ENVP_OBJ))

###

all: $(MAIN_OBJ_DIR) $(EXEC_OBJ_DIR) $(BTIN_OBJ_DIR) $(ENVP_OBJ_DIR) $(NAME)

$(MAIN_OBJ_DIR) $(EXEC_OBJ_DIR) $(BTIN_OBJ_DIR) $(ENVP_OBJ_DIR):
	mkdir -p $(MAIN_OBJ_DIR) $(EXEC_OBJ_DIR) $(BTIN_OBJ_DIR) $(ENVP_OBJ_DIR)

$(NAME): $(MAIN_OBJ) $(EXEC_OBJ) $(BTIN_OBJ) $(ENVP_OBJ)
	@ar rcs $(NAME) $^
	@echo -e "\033[1m\033[32m$(NAME) created!\033[0m"

$(addprefix $(MAIN_OBJ_DIR), %.o): $(addprefix $(MAIN_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) -I../libft/includes -I.. -I. -c $< -o $@ -MMD

$(addprefix $(EXEC_OBJ_DIR), %.o): $(addprefix $(EXEC_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) -I../libft/includes -I.. -I. -c $< -o $@ -MMD

$(addprefix $(BTIN_OBJ_DIR), %.o): $(addprefix $(BTIN_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) -I../libft/includes -I.. -c $< -o $@ -MMD

$(addprefix $(ENVP_OBJ_DIR), %.o): $(addprefix $(ENVP_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) -I../libft/includes -I.. -c $< -o $@ -MMD

clean:
	@echo -e "\033[31mDeleting...\033[0m"
	@rm -rf temp
	@echo -e "\033[31m\033[1mObject files deleted!\033[0m\033[31m\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo -e "\033[31m\033[1m$(NAME), etc. files deleted!\033[0m"

re: fclean all

include $(wildcard $(D_FILES))

.PHONY: all, re, clean, fclean, bonus, run_script, crtmpdirs, libutil
