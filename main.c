/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:40:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/11/18 11:46:56 by sgertrud         ###   ########.fr       */
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
	struct termios term;
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
	set_terminal_mode(term,term_name);
	str = "NE 4";
	write(1, GREEN, 5);
	write(1,"minishell: ", 12);
	write(1, RESET, 5);
	str = read_line(term,_envp);
	while (str && *str && *str != 4)
	{
		temp = str;
		while (*str && *str != '\n')
		{
			command = parse_command(&str, _envp);
			do_command(command, &_envp, term);
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
		str = read_line(term,_envp);
	}
	do_command((char*[2]){"exit", 0}, &_envp,term);
	return (0);
}