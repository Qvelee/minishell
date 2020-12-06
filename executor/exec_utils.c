/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:42:11 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/06 16:41:53 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int			end_of_commands(t_exec *exec)
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
	if ((dup2(exec->tmp_in, 0) == -1) || (dup2(exec->tmp_out, 1) == -1))
		exec->return_value = error_fd(NULL, -1, -1, -1);
	if ((exec->status = try_close(exec->tmp_in, exec->tmp_out, -1)))
		exec->return_value = exec->status;
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
