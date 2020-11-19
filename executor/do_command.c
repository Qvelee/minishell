/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:10:57 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/19 16:25:55 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>

static int		run_built_in(int index, char **args, t_envp **envp_list,\
				t_term term)
{
	int		return_value;

	return_value = -2;
	if (index == 0)
		return_value = mini_echo(args);
	if (index == 1)
		return_value = mini_pwd();
	if (index == 2)
		return_value = mini_cd(args, envp_list);
	if (index == 3)
		return_value = mini_export(args, envp_list);
	if (index == 4)
		return_value = mini_unset(args, envp_list);
	if (index == 5)
		return_value = mini_env(*envp_list);
	if (index == 6)
	{
		remove_terminal_mode(term);
		envp_lst_clear(envp_list, free);
		return_value = mini_exit(args);
	}
	return (return_value);
}

int		built_in(char **args, t_envp **envp_list, t_term term)
{
	char	*commands[8] =	{"echo", "pwd", "cd", "export", \
							"unset", "env", "exit", NULL};
	int		index;

	index = -1;
	while (commands[++index] && args[0])
		if (!ft_strncmp(commands[index], args[0], 7))
			return (run_built_in(index, args, envp_list, term));
	return (-2);
}

int				do_command(char **args, t_envp **envp_list, t_term term)
{
	int		return_value;
	t_term	t;
	
	t = term;
	// int		index = -1;
	// while (args[++index])
		// printf("%s\n", args[index]);
	if ((return_value = built_in(args, envp_list, term) == -2))
		return_value = command(args, envp_list);
	// printf("end of do_command\n");
	return (return_value);
}
