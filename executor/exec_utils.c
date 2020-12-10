/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:42:11 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/10 18:49:56 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	wait_all_processes(t_exec *exec)
{
	int		error;

	error = 0;
	exec->index = -1;
	while (++exec->index < exec->count)
		if (exec->pids[exec->index] < 0)
		{
			exec->pids[exec->index] *= -1;
			if ((waitpid(exec->pids[exec->index], &exec->status, \
												WUNTRACED) == -1))
				error_print_return(NULL);
			while (!WIFEXITED(exec->status) && !WIFSIGNALED(exec->status))
				if ((waitpid(exec->pids[exec->index], &exec->status, \
					WUNTRACED) == -1))
					error_print_return(NULL);
			if (check_fatal_error((exec->return_value = \
					WEXITSTATUS(exec->status))))
				error = exec->return_value;
		}
		else
			exec->return_value = exec->pids[exec->index];
	if (error)
		return (error);
	return (exec->return_value);
}

int			error_running(int return_value, t_commands *command, t_exec *exec)
{
	wait_all_processes(exec);
	try_close(&command->fd_in, &command->fd_out);
	try_close(&exec->fd_in, &exec->fd_out);
	if ((dup2(exec->tmp_in, 0) == -1))
		error_print_return("can't restore stdin");
	if ((dup2(exec->tmp_out, 1) == -1))
		error_print_return("can't restore stout");
	try_close(&exec->tmp_in, &exec->tmp_out);
	free(exec->pids);
	return (return_value);
}

int			end_of_commands(t_exec *exec)
{
	int		ret;
	int		tmp;

	ret = wait_all_processes(exec);
	if ((dup2(exec->tmp_in, 0) == -1))
		ret = error_print_return("can't restore stdin");
	if ((dup2(exec->tmp_out, 1) == -1))
		ret = error_print_return("can't restore stout");
	if ((tmp = try_close(&exec->tmp_in, &exec->tmp_out)))
		ret = tmp;
	free(exec->pids);
	return (ret);
}

int			init_exec(t_exec *exec, t_commands *commands)
{
	int		index;

	if ((exec->tmp_in = dup(0)) == -1)
		return (error_fd(NULL, -1, -11));
	if ((exec->tmp_out = dup(1)) == -1)
		return (error_fd(NULL, exec->tmp_in, -1));
	exec->count = comm_lst_size(commands);
	if (!(exec->pids = (int*)malloc(sizeof(int) * exec->count)))
	{
		try_close(&exec->tmp_in, &exec->tmp_out);
		return (error_print_return(NULL));
	}
	index = -1;
	while (++index < exec->count)
		exec->pids[index] = 0;
	exec->index = 0;
	if ((exec->fd_in = dup(exec->tmp_in)) == -1)
	{
		free(exec->pids);
		return (error_fd(NULL, exec->tmp_in, exec->tmp_out));
	}
	return (0);
}
