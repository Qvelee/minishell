/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:10:57 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/01 15:55:53 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>

static int	save_ret_value(int value, t_envp **envp_list)
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

int			run_simple_command(char **args, t_envp **envp_list, t_term term)
{
	int		return_value;

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

int			run_commands(t_commands *commands, t_envp **envp_list, t_term term)
{
	int			return_value;
	int			fd_pipe[2];
	int			fd_out;
	int			fd_in;
	const int	tmp_in = dup(0);
	const int	tmp_out = dup(1);

	fd_in = dup(tmp_in);
	while (commands)
	{
		dup2(fd_in, 0);
		close(fd_in);
		if (commands->next)
		{
			pipe(fd_pipe);
			fd_in = fd_pipe[0];
			fd_out = fd_pipe[1];
		}
		else
			fd_out = dup(tmp_out);
		dup2(fd_out, 1);
		close(fd_out);
		return_value = run_simple_command(commands->command, envp_list, term);
		commands = commands->next;
	}
	dup2(tmp_in, 0);
	dup2(tmp_out, 1);
	close(tmp_in);
	close(tmp_out);
	int		status;
	do
		waitpid(return_value, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status));
	return (return_value);
}

int			do_command(char **args, t_envp **envp_list, t_term term)
{
	int			return_value;
	t_commands	*commands;

	parse_command_ex(args, &commands);
	return_value = run_commands(commands, envp_list, term);
	comm_lst_clr(&commands);
	return (return_value);
}
