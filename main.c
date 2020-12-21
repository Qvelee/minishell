/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:40:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/21 07:22:16 by sgertrud         ###   ########.fr       */
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

void ft_sigint(int __attribute__ ((unused))sig)
{
	write (1,&(char){10},1);
	write(1, GREEN, 5);
	write(1,"minishell: ", 12);
	write(1, RESET, 5);

	*(*get_line()->str) = 0;
	*get_line()->i = 0;
	get_line()->sig = 1;
}

void ft_nothing(int __attribute__ ((unused))sig)
{

}

int	main(int __attribute__ ((unused))argc, char __attribute__ ((unused))**argv, char **envp)
{
	char c;
	char *str;
	char **command;
	char *temp;
	char *term_name;
	t_envp *_envp;
	char **my_exit;
	int i;
	char *histfile;

	signal(SIGINT,ft_sigint);
	signal(SIGQUIT, ft_nothing);

	my_exit = malloc(2*sizeof(char*));
	my_exit[0] = ft_strdup("exit");
	my_exit[1] = 0;
	_envp = envp_create_list(envp);
	term_name = envp_get_var_value(_envp,"TERM");
	if (set_terminal_mode(term_name) == -1)
		do_command((char*[3]){"exit", "1", 0}, &_envp);
	str = "NE 4";
	write(1, GREEN, 5);
	write(1,"minishell: ", 12);
	write(1, RESET, 5);
	//printf("%s\n",envp_get_var_value(_envp,"_"));
	str = read_line(_envp);
	histfile = ft_strjoin_gnl(ft_substr(envp_get_var_value(_envp,"_"),0,ft_strlen(envp_get_var_value(_envp,"_")) - 9),".minishell_history");

	envp_add_to_lst_back(envp_lst_new(envp_create_envp_str("HISTFILE",histfile),0), &_envp);
	while (str && *str && *str != 4)
	{
		get_line()->sig = 0;
		temp = str;
		while (*str && *str != '\n')
		{
			if ((c = check_validity(str)))
			{
				write(1, "minishell: syntax error near unexpected token '", 47);
				if (c == '\n')
					write(1, "\\n",2);
				else
					write(1, &c, 1);
				write(1, "'\n", 2);
				break;
			}
			command = parse_command(&str, _envp);
			remove_terminal_mode();
			do_command(command, &_envp);
			set_terminal_mode(envp_get_var_value(_envp, "TERM"));
			i = 0;
			while (command[i])
				free(command[i++]);
			free(command);
			str++;
		}
		if (!get_line()->sig)
		{
			write(1, GREEN, 5);
			write(1,"minishell: ", 12);
			write(1, RESET, 5);
		}
		free(temp);
		str = read_line(_envp);
	}
	do_command((char*[2]){"exit", 0}, &_envp);
	return (0);
}