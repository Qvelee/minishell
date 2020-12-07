/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:40:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/07 20:01:18 by nelisabe         ###   ########.fr       */
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

void ft_nothing(int __attribute__ ((unused))sig)
{
	write (1,&(char){10},1);
	write(1, GREEN, 5);
	write(1,"minishell: ", 12);
	write(1, RESET, 5);
}

int	main(int __attribute__ ((unused))argc, char __attribute__ ((unused))**argv, char **envp)
{
	char *str;
	char **command;
	char *temp;
	char *term_name;
	t_envp *_envp;
	char **my_exit;
	int i;

	signal(SIGINT,ft_nothing);
	my_exit = malloc(2*sizeof(char*));
	my_exit[0] = ft_strdup("exit");
	my_exit[1] = 0;
	_envp = envp_create_list(envp);
	term_name = envp_get_var_value(_envp,"TERM");
	set_terminal_mode(term_name);
	str = "NE 4";
	write(1, GREEN, 5);
	write(1,"minishell: ", 12);
	write(1, RESET, 5);
	str = read_line(_envp);
	while (str && *str && *str != 4)
	{
		temp = str;
		while (*str && *str != '\n')
		{
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
		free(temp);
		write(1, GREEN, 5);
		write(1,"minishell: ", 12);
		write(1, RESET, 5);
		str = read_line(_envp);
	}
	do_command((char*[2]){"exit", 0}, &_envp);
	return (0);
}