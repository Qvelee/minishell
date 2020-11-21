/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:10:57 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/21 14:53:23 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>

static int		run_built_in(int index, char **args, t_envp **envp_list,\
				t_term term)
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
	return (127);
}

int		save_ret_value(int value, t_envp **envp_list)
{
	char	*value_to_save;
	char	*temp;

	if (!(temp = ft_itoa(value)))
		return (12);
	if (!(value_to_save = envp_create_envp_str("?", temp)))
	{
		free(temp);
		return (12);
	}
	free(temp);
	if (envp_replace_variable(envp_list, value_to_save, 0))
	{
		free(value_to_save);
		return (12);
	}
	return (0);
}

int			do_command(char **args, t_envp **envp_list, t_term term)
{
	static int	return_value;
	t_term		t;

	t = term;
	return_value = built_in(args, envp_list, term);
	if (return_value == 0)
		;
	else if (return_value != 127)
		check_memory_error(return_value, args, envp_list, term);
	else
	{
		return_value = command(args, envp_list);
		if (return_value == 0)
			;
		else if (return_value != 127)
			check_memory_error(return_value, args, envp_list, term);
		else
			error_command_not_found(args[0]);
	}
	if (save_ret_value(return_value, envp_list))
		check_memory_error(12, args, envp_list, term);
	return (return_value);
}
