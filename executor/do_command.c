/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:10:57 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/18 15:58:02 by nelisabe         ###   ########.fr       */
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

static int		command(char **args, t_envp **envp_list)
{
	char	**envp;
	pid_t	pid;
	int		return_value;

	return_value = -2;
	envp = envp_lst_to_matrix(*envp_list);
	pid = fork();
	if (pid == 0)
		execve(args[0], args, envp);
	else if (pid > 0)
		wait(&return_value);
	free(envp);
	return (return_value);
}

int				do_command(char **args, t_envp **envp_list, t_term term)
{
	int		return_value;
	t_term	t;
	
	t = term;
	return_value = built_in(args, envp_list, term);
	return_value = command(args, envp_list);
	return (return_value);
}
