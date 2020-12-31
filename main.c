/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 23:40:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/29 16:42:57 by sgertrud         ###   ########.fr       */
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
//	signal(SIGSEGV, ft_sigint);
}

void	set_sh(char **envp)
{
	char	*shlvl;

	signals();
	(*get_envp()) = envp_create_list(envp);
	if (set_terminal_mode(envp_get_var_value((*get_envp()), "TERM")) == -1)
		do_command((char *[3]){ft_strdup("exit"),
		ft_strdup("1"), 0}, get_envp());
	add_histfile((*get_envp()));
	shlvl = ft_itoa(ft_atoi(envp_get_var_value(*get_envp(), "SHLVL")) + 1);
	envp_replace_variable(get_envp(), envp_create_envp_str("SHLVL", shlvl), 1);
	envp_add_to_lst_back(envp_lst_new(envp_create_envp_str("MS_SUBSHELL", "0"),
	0), get_envp());
	free(shlvl);
}

int		main(int __attribute__((unused)) argc,
	char __attribute__((unused)) **argv, char **envp)
{
	char	*str;
	char	*temp;

	set_sh(envp);
	invite("minishell: ");
	save_ret_value(0, get_envp());
	str = read_line((*get_envp()));
	while (str && *str != 4 && *str)
	{
		g_line()->sig = 0;
		temp = str;
		one_command(&str, (get_envp()));
		invite("minishell: ");
		free(temp);
		str = read_line((*get_envp()));
	}
	do_command((char *[2]){ft_strdup("exit"), 0}, get_envp());
	return (0);
}
