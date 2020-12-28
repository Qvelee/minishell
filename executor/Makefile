# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 14:15:44 by nelisabe          #+#    #+#              #
#    Updated: 2020/12/28 18:25:28 by nelisabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				libexec.a

COMP =				gcc -g

FLAGS =				-Wall -Wextra -Werror

EXEC_HEADER = 		./executor.h

INCLUDES =			-I../libft/includes -I.. -I.

#SRC DIRS

EXEC_SRC_DIR =		./
COMM_SRC_DIR =		./command_treatment/
BTIN_SRC_DIR =		./built-ins/
ENVP_SRC_DIR =		./envp/

#SRC

EXEC_SRC =			do_command.c \
					executor.c \
					execute_command.c \
					errors_management.c \
					errors_management_2.c \
					exec_utils.c \
					exit_minishell.c\
					remove_slashes.c

COMM_SRC =			brackets_treatment.c \
					parse_command.c \
					redirects_treatment.c \
					get_input.c \
					comm_utils.c

BTIN_SRC =			built_in.c \
					mini_echo.c \
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

EXEC_OBJ_DIR =		./temp/
COMM_OBJ_DIR =		./temp/command_treatment/
BTIN_OBJ_DIR =		./temp/built-ins/
ENVP_OBJ_DIR =		./temp/envp/

#OBJ

EXEC_OBJ =			$(addprefix $(EXEC_OBJ_DIR), $(EXEC_SRC:.c=.o))
COMM_OBJ =			$(addprefix $(COMM_OBJ_DIR), $(COMM_SRC:.c=.o))
BTIN_OBJ =			$(addprefix $(BTIN_OBJ_DIR), $(BTIN_SRC:.c=.o))
ENVP_OBJ =			$(addprefix $(ENVP_OBJ_DIR), $(ENVP_SRC:.c=.o))


D_FILES = $(patsubst %.o, %.d, $(COMM_OBJ)) $(patsubst %.o, %.d, $(EXEC_OBJ)) $(patsubst %.o, %.d, $(BTIN_OBJ)) $(patsubst %.o, %.d, $(ENVP_OBJ))

###

all: $(COMM_OBJ_DIR) $(EXEC_OBJ_DIR) $(BTIN_OBJ_DIR) $(ENVP_OBJ_DIR) $(NAME)

$(COMM_OBJ_DIR) $(EXEC_OBJ_DIR) $(BTIN_OBJ_DIR) $(ENVP_OBJ_DIR):
	mkdir -p $(COMM_OBJ_DIR) $(EXEC_OBJ_DIR) $(BTIN_OBJ_DIR) $(ENVP_OBJ_DIR)

$(NAME): $(COMM_OBJ) $(EXEC_OBJ) $(BTIN_OBJ) $(ENVP_OBJ)
	@ar rcs $(NAME) $^
	@echo -e "\033[1m\033[32m$(NAME) created!\033[0m"

$(addprefix $(EXEC_OBJ_DIR), %.o): $(addprefix $(EXEC_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(addprefix $(COMM_OBJ_DIR), %.o): $(addprefix $(COMM_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) $(INCLUDES) -fPIE -c $< -o $@ -MMD

$(addprefix $(BTIN_OBJ_DIR), %.o): $(addprefix $(BTIN_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

$(addprefix $(ENVP_OBJ_DIR), %.o): $(addprefix $(ENVP_SRC_DIR), %.c)
	@echo -e "\033[36mCompiling $< ..."
	@$(COMP) $(FLAGS) $(INCLUDES) -c $< -o $@ -MMD

clean:
	@echo -e "\033[31mDeleting...\033[0m"
	@rm -rf temp
	@echo -e "\033[31m\033[1mObject files deleted!\033[0m\033[31m\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo -e "\033[31m\033[1m$(NAME), etc. files deleted!\033[0m"

re: fclean all

bonus: all

include $(wildcard $(D_FILES))

.PHONY: all, re, clean, fclean
