/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:42:11 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/06 19:53:21 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	wait_all_processes(t_exec *exec)
{
	exec->index = -1;
	while (++exec->index < exec->count)
	{
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
			exec->return_value = WEXITSTATUS(exec->status);
		}
		else
			exec->return_value = exec->pids[exec->index];
	}
	return (exec->return_value);
}

int			error_running(int return_value, t_commands *command, t_exec *exec)
{
	int		ret;
	int		tmp;

	wait_all_processes(exec);
	if ((tmp = error_print_return(NULL)))
		ret = tmp;
	if ((tmp = try_close(command->fd_in, command->fd_out, -1)))
		ret = tmp;
	if ((tmp = try_close(exec->fd_in, exec->fd_out, -1)))
		ret = tmp;
	if ((dup2(exec->tmp_in, 0) == -1))
		ret = error_print_return(NULL);
	if ((dup2(exec->tmp_out, 1) == -1))
		ret = error_print_return(NULL);
	if ((tmp = try_close(exec->tmp_in, exec->tmp_out, -1)))
		ret = tmp;
	free(exec->pids);
	return (ret);
}

int			end_of_commands(t_exec *exec)
{
	int 	temp;

	wait_all_processes(exec);
	if ((dup2(exec->tmp_in, 0) == -1))
		exec->return_value = error_print_return(NULL);
	if ((dup2(exec->tmp_out, 1) == -1))
		exec->return_value = error_print_return(NULL);
	if ((temp = try_close(exec->tmp_in, exec->tmp_out, -1)))
		exec->return_value = temp;
	free(exec->pids);
	return (exec->return_value);
}

int			init_exec(t_exec *exec, t_commands *commands)
{
	int		index;

	if ((exec->tmp_in = dup(0)) == -1)
		return (error_fd(NULL, -1, -1, -1));
	if ((exec->tmp_out = dup(1)) == -1)
		return (error_fd(NULL, exec->tmp_in, -1, -1));
	exec->count = comm_lst_size(commands);
	if (!(exec->pids = (int*)malloc(sizeof(int) * exec->count)))
	{
		try_close(exec->tmp_in, exec->tmp_out, -1);
		return (12);
	}
	index = -1;
	while (++index < exec->count)
		exec->pids[index] = 0;
	exec->index = 0;
	if ((exec->fd_in = dup(exec->tmp_in)) == -1)
	{
		free(exec->pids);
		return (error_fd(NULL, exec->tmp_in, exec->tmp_out, -1));
	}
	return (0);
}
