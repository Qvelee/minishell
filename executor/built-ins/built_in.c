/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:52:23 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/06 18:56:01 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	run_built_in(int index, char **args, t_envp **envp_list, \
							int mode, t_term term)
{
	int		return_value;

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
		return_value = mini_exit(args, envp_list, mode, term);
	return (return_value);
}

int			built_in(char **args, t_envp **envp_list, int mode, t_term term)
{
	char	*commands[8] =	{"echo", "pwd", "cd", "export", \
							"unset", "env", "exit", NULL};
	int		index;
	pid_t	pid;

	index = -1;
	while (commands[++index] && args[0])
		if (!ft_strncmp(commands[index], args[0], 7))
		{
			if (!mode || mode == 2)
				return (run_built_in(index, args, envp_list, mode, term));
			else
			{
				pid = fork();
				if (pid == 0)
					exit(run_built_in(index, args, envp_list, mode, term));
				else if (pid > 0)
					return (pid * -1);
				else
					return (error_print_return(args[0]));
			}
		}
	return (127);
}
