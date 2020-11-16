/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:10:57 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/16 19:57:46 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>

static int		run_built_in(int index, char **args, t_envp **envp_list,\
				t_term term)
{
	int		return_value;

	return_value = 0;
	if (index == 0)
		mini_echo(args);
	if (index == 1)
		return_value = mini_pwd();
	if (index == 2)
		return_value = mini_cd(args, envp_list);
	if (index == 3)
		return_value = mini_export(args, envp_list);
	if (index == 4)
		return_value = mini_unset(args, envp_list);
	if (index == 5)
		mini_env(*envp_list);
	if (index == 6)
	{
		remove_terminal_mode(term);
		envp_lst_clear(envp_list, free);
		mini_exit(args);
	}
	return (return_value);
}

int				do_command(char **args, t_envp **envp_list, t_term term)
{
	char	*commands[8] =	{"echo", "pwd", "cd", "export", \
							"unset", "env", "exit", NULL};
	int		index;

	index = -1;
	while (commands[++index] && args[0])
		if (!ft_strncmp(commands[index], args[0], 7))
			return (run_built_in(index, args, envp_list, term));
	return (0);
}
