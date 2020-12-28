/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:40:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/28 17:55:49 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "get_static.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include "main.h"
#include "libft.h"
#include <signal.h>
#include "executor.h"

void	signals(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_nothing);
	signal(SIGSEGV, ft_sigint);
}

int		main(int __attribute__((unused)) argc,
	char __attribute__((unused)) **argv, char **envp)
{
	char	*str;
	char	*temp;

	if (set_terminal_mode(envp_get_var_value((*get_envp()), "TERM")) == -1)
		do_command((char *[3]){ft_strdup("exit"),
		ft_strdup("1"), 0}, get_envp(), 0);
	signals();
	(*get_envp()) = envp_create_list(envp);
	add_histfile((*get_envp()));
	invite("minishell: ");
	save_ret_value(0, get_envp());
	str = read_line((*get_envp()));
	while (str && *str != 4 && *str)
	{
		g_line()->sig = 0;
		temp = str;
		if (!syntax_error(check_validity(str)))
			one_command(&str, (get_envp()));
		invite("minishell: ");
		free(temp);
		str = read_line((*get_envp()));
	}
	do_command((char *[2]){ft_strdup("exit"), 0}, get_envp(), 0);
	return (0);
}
