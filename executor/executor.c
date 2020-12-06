/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:42:49 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/06 19:57:00 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//do the correct return system

static int	run_simple_command(char **args, t_envp **envp_list, int mode, \
															t_term term)
{
	int		return_value;

	return_value = built_in(args, envp_list, mode, term);
	if (return_value <= 0)
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

static int	run_command(t_commands *command, t_envp **envp_list, int count, \
															t_term term)
{
	int		mode;

	mode = 0;
	if (count > 1)
		mode = 1;
	if (!mode && (!ft_strcmp(command->command[0], "exit") && command->fd_out))
		mode = 2;
	if (command->fd_in != -1 && command->fd_out != -1)
		return (run_simple_command(command->command, envp_list, mode, term));
	else
		return (1);
}

static int	set_fd_out(int *current_fd_out, int *command_fd_out)
{
	int		ret;

	ret = 0;
	if (*command_fd_out > 0)
	{
		if ((ret = try_close(*current_fd_out, -1, -1)))
			return (ret);
		*current_fd_out = *command_fd_out;
	}
	if (dup2(*current_fd_out, 1) == -1)
		return (error_fd(NULL, *current_fd_out, -1, -1));
	if ((ret = try_close(*current_fd_out, -1, -1)))
		return (ret);
	return (ret);
}

static int	set_fd_in(int *current_fd_in, int *command_fd_in)
{
	int		ret;

	ret = 0;
	if (*command_fd_in > 0)
	{
		if ((ret = try_close(*current_fd_in, -1, -1)))
			return (ret);
		*current_fd_in = *command_fd_in;
	}
	if (dup2(*current_fd_in, 0) == -1)
		return (error_fd(NULL, *current_fd_in, -1, -1));
	if ((ret = try_close(*current_fd_in, -1, -1)))
		return (ret);
	return (ret);
}

int			run_commands(t_commands *commands, t_envp **envp_list, t_term term)
{
	t_exec	exec;

	if ((exec.return_value = init_exec(&exec, commands)))
		return (exec.return_value);
	while (commands)
	{
		if ((exec.return_value = set_fd_in(&exec.fd_in, &commands->fd_in)))
			return (error_running(exec.return_value, commands, &exec));
		if (commands->next)
		{
			if ((exec.return_value = pipe(exec.fd_pipe)) == -1)
				return (error_running(exec.return_value, commands, &exec));
			exec.fd_in = exec.fd_pipe[0];
			exec.fd_out = exec.fd_pipe[1];
		}
		else
			if ((exec.fd_out = dup(exec.tmp_out)) == -1)
				return (error_running(exec.fd_out, commands, &exec));
		if ((exec.return_value = set_fd_out(&exec.fd_out, &commands->fd_out)))
			return (error_running(exec.return_value, commands, &exec));
		exec.return_value = run_command(commands, envp_list, exec.count, term);
		commands = commands->next;
		exec.pids[exec.index++] = exec.return_value;
	}
	return (end_of_commands(&exec));
}
