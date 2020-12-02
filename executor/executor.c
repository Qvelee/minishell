/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:42:49 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/02 20:07:01 by nelisabe         ###   ########.fr       */
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

int			init_exec(t_exec *exec, t_commands *commands)
{
	int		index;

	exec->tmp_in = dup(0);
	exec->tmp_out = dup(1);
	exec->count = comm_lst_size(commands);
	if (!(exec->pids = (int*)malloc(sizeof(int) * exec->count)))
	{
		close(exec->tmp_in);
		close(exec->tmp_out);
		return (12);
	}
	index = -1;
	while (++index < exec->count)
		exec->pids[index] = 0;
	exec->index = 0;
	return (0);
}

int			end_of_commands(t_exec *exec)
{
	dup2(exec->tmp_in, 0);
	dup2(exec->tmp_out, 1);
	close(exec->tmp_in);
	close(exec->tmp_out);
	exec->index = -1;
	while (++exec->index < exec->count)
	{
		if (exec->pids[exec->index] < 0)
		{
			exec->pids[exec->index] *= -1;
			waitpid(exec->pids[exec->index], &exec->status, WUNTRACED);
			while (!WIFEXITED(exec->status) && !WIFSIGNALED(exec->status))
				waitpid(exec->pids[exec->index], &exec->status, WUNTRACED);
			exec->return_value = WEXITSTATUS(exec->status);
		}
		else
			exec->return_value = exec->pids[exec->index];
	}
	free(exec->pids);
	return (exec->return_value);
}

int			run_commands(t_commands *commands, t_envp **envp_list, t_term term)
{
	t_exec	exec;

	init_exec(&exec, commands);
	exec.fd_in = dup(exec.tmp_in);
	while (commands)
	{
		dup2(exec.fd_in, 0);
		close(exec.fd_in);
		if (commands->next)
		{
			pipe(exec.fd_pipe);
			exec.fd_in = exec.fd_pipe[0];
			exec.fd_out = exec.fd_pipe[1];
		}
		else
			exec.fd_out = dup(exec.tmp_out);
		if (commands->fd_out != -1)
		{
			close(exec.fd_out);
			exec.fd_out = commands->fd_out;
		}
		dup2(exec.fd_out, 1);
		close(exec.fd_out);
		exec.return_value = run_simple_command(commands->command, envp_list, term);
		commands = commands->next;
		exec.pids[exec.index++] = exec.return_value;
	}
	return (end_of_commands(&exec));
}
