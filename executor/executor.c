/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:42:49 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/07 17:44:29 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//do the correct return system
//not destroy terminal mode in exit if pipe

static int	run_command(t_commands *commands, t_envp **envp_list, int count, \
															t_term term)
{
	int		return_value;
	int		mode;

	mode = 0;
	if (count > 1)
		mode = 1;
	if (!mode && (!ft_strcmp(commands->command[0], "exit") && commands->fd_out))
		mode = 2;
	if (commands->fd_in != -1 && commands->fd_out != -1)
	{
		if ((return_value = \
				built_in(commands->command, envp_list, mode, term)) == 127)
			return_value = command(commands->command, envp_list);
	}
	else
		return_value = 1;
	return (return_value);
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

static int	do_pipe(int *fd_pipe, int *fd_in, int *fd_out)
{
	int 	ret;

	if ((ret = pipe(fd_pipe)) == -1)
		return (1);
	*fd_in = fd_pipe[0];
	*fd_out = fd_pipe[1];
	return (0);
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
			if (do_pipe(exec.fd_pipe, &exec.fd_in, &exec.fd_out))
				return (error_running(exec.return_value, commands, &exec));
		if (!commands->next)
			if ((exec.fd_out = dup(exec.tmp_out)) == -1)
				return (error_running(exec.fd_out, commands, &exec));
		if ((exec.return_value = set_fd_out(&exec.fd_out, &commands->fd_out)))
			return (error_running(exec.return_value, commands, &exec));
		exec.return_value = run_command(commands, envp_list, exec.count, term);
		if (check_fatal_error(exec.return_value))
			return (error_running(exec.return_value, commands, &exec));
		exec.pids[exec.index++] = exec.return_value;
		commands = commands->next;
	}
	return (end_of_commands(&exec));
}
