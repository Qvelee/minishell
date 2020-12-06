/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:42:49 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/06 17:01:24 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//need to do: run built-ins in fork if pipe

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
		if (return_value < 0)
			;
		else if (return_value != 127)
			check_memory_error(return_value, args, envp_list, term);
	}
	return (return_value);
}

static int	set_fd_out(int *current_fd_out, int *command_fd_out)
{
	int		ret;

	ret = 0;
	if (*command_fd_out > 0)
	{
		try_close(*current_fd_out, -1, -1);
		*current_fd_out = *command_fd_out;
	}
	dup2(*current_fd_out, 1);
	try_close(*current_fd_out, -1, -1);
	return (ret);
}

static int	set_fd_in(int *current_fd_in, int *command_fd_in)
{
	int		ret;

	ret = 0;
	if (*command_fd_in > 0)
	{
		try_close(*current_fd_in, -1, -1);
		*current_fd_in = *command_fd_in;
	}
	dup2(*current_fd_in, 0);
	try_close(*current_fd_in, -1, -1);
	return (ret);
}

int			run_commands(t_commands *commands, t_envp **envp_list, t_term term)
{
	t_exec	exec;

	if ((exec.return_value = init_exec(&exec, commands)))
		return (exec.return_value);
	while (commands)
	{
		set_fd_in(&exec.fd_in, &commands->fd_in);
		if (commands->next)
		{
			pipe(exec.fd_pipe);
			exec.fd_in = exec.fd_pipe[0];
			exec.fd_out = exec.fd_pipe[1];
		}
		else
			exec.fd_out = dup(exec.tmp_out);
		set_fd_out(&exec.fd_out, &commands->fd_out);
		if (commands->fd_in != -1 && commands->fd_out != -1)
			exec.return_value = \
				run_simple_command(commands->command, envp_list, term);
		else
			exec.return_value = 1;
		commands = commands->next;
		exec.pids[exec.index++] = exec.return_value;
	}
	return (end_of_commands(&exec));
}
