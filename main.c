/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:40:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/28 16:17:03 by nelisabe         ###   ########.fr       */
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
	t_envp	*envp_;

	signals();
	envp_ = envp_create_list(envp);
	add_histfile(envp_);
	if (set_terminal_mode(envp_get_var_value(envp_, "TERM")) == -1)
		do_command((char *[3]){ft_strdup("exit"), ft_strdup("1"), 0}, &envp_, \
			0);
	invite("minishell: ");
	(*get_envp()) = envp_;
	str = read_line(envp_);
	while (str && *str != 4 && *str)
	{
		g_line()->sig = 0;
		temp = str;
		if (!syntax_error(check_validity(str)))
			one_command(&str, &envp_);
		invite("minishell: ");
		free(temp);
		str = read_line(envp_);
	}
	do_command((char *[2]){ft_strdup("exit"), 0}, &envp_, 0);
	return (0);
}
