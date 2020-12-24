/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:40:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/24 23:39:33 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include "parse.h"
#include "main.h"
#include "libft.h"
#include "signal.h"
#include "executor.h"

void ft_sigint(int __attribute__((unused)) sig)
{
	write(1, "\n", 1);
	write(1, GREEN, 5);
	write(1, "minishell: ", 11);
	write(1, RESET, 5);

	save_ret_value(130, get_envp());

//	printf("\n|%s|\n", *get_line()->str);
	if (get_line()->str && *(get_line()->str))
		*(*get_line()->str) = 0;
	*get_line()->i = 0;
	get_line()->sig = 1;
}

void ft_nothing(int __attribute__((unused)) sig)
{
}

void add_histfile(t_envp *_envp)
{
	char *histfile;
	int len;
	char *temp = envp_get_var_value(_envp, "_");
	char *home = envp_get_var_value(_envp, "HOME");

	histfile = 0;
	if (home)
		histfile = ft_strjoin(home, "/.minishell_history");
	else if (temp)
	{
		len = ft_strlen(temp) - 9;
		if (!ft_strncmp(&temp[len], "minishell", 9))
			histfile = ft_strjoin_gnl(ft_substr(temp, 0, len), ".minishell_history");
	}
	if (histfile)
		envp_add_to_lst_back(envp_lst_new(envp_create_envp_str("HISTFILE", histfile), 0), &_envp);
	free(histfile);
}

int main(int __attribute__((unused)) argc, char __attribute__((unused)) * *argv, char **envp)
{
	char c;
	char *str;
	char **command;
	char *temp;
	char *term_name;
	t_envp *_envp;
	char **my_exit;
	int i;

	*(get_line()) = (t_line){&str, &i, 0, BUFF_SIZE};

	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_nothing);

	my_exit = malloc(2 * sizeof(char *));
	my_exit[0] = ft_strdup("exit");
	my_exit[1] = 0;
	_envp = envp_create_list(envp);
	add_histfile(_envp);
	term_name = envp_get_var_value(_envp, "TERM");
	if (set_terminal_mode(term_name) == -1)
		do_command((char *[3]){"exit", "1", 0}, &_envp);
	str = "NE 4";
	write(1, GREEN, 5);
	write(1, "minishell: ", 11);
	write(1, RESET, 5);
	//printf("%s\n",envp_get_var_value(_envp,"_"));

	(*get_envp()) = _envp;

	//printf("|%s|\n",histfile);

	str = read_line(_envp);
	while (str && *str != 4)
	{
		get_line()->sig = 0;
		temp = str;
		//*get_line()->str = temp;
		while (*str && *str != '\n')
		{
			if ((c = check_validity(str)))
			{
				write(1, "minishell: syntax error near unexpected token '", 47);
				if (c == '\n')
					write(1, "\\n", 2);
				else
					write(1, &c, 1);
				write(1, "'\n", 2);
				break;
			}
			command = parse_command(&str, _envp);
			remove_terminal_mode();
			get_line()->str = &str;
			if (!get_line()->sig && command && *command)
				do_command(command, &_envp);
			set_terminal_mode(envp_get_var_value(_envp, "TERM"));
			i = 0;
			//sleep(1);
			while (command[i])
				free(command[i++]);
			free(command);
			if (*str)
				str++;
		}
		if (!get_line()->sig)
		{
			write(1, GREEN, 5);
			write(1, "minishell: ", 11);
			write(1, RESET, 5);
		}
		free(temp);
		str = read_line(_envp);
	}
	do_command((char *[2]){ft_strdup("exit"), 0}, &_envp);
	return (0);
}