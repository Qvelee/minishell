/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_treatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:24:33 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/28 23:09:24 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>

int		wait_subprocess(pid_t pid, int *ret)
{
	int		status;
	
	if ((waitpid(pid, &status, WUNTRACED) == -1))
		error_print_return(NULL);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		if ((waitpid(pid, &status, WUNTRACED) == -1))
			error_print_return(NULL);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			*ret = 130;
		if (WTERMSIG(status) == 3)
			*ret = 131;
	}
	else 
		check_fatal_error((*ret = WEXITSTATUS(status)));
	return (0);
}

int		open_bracket_found(t_shell *shell, int *ret)
{
	pid_t	pid;
	int		index;
	
	pid = fork();
	if (pid == 0)
	{
		shell->lvl++;
		shell->command = &shell->command[1];
		return (2);
	}
	else if (pid > 0)
		wait_subprocess(pid, ret);
	index = -1;
	while (shell->command[++index] && ft_strcmp(shell->command[index], ")"))
		;
	if (shell->command[index])
	{
		shell->command = &shell->command[index + 1];
		shell->mode = 0;
		if (shell->command[0])
			exit(*ret);
		shell->flag = 0;
		return (0);
	}
	else
	{
		shell->flag = 1;
		return (1);
	}
}

int		command_found(t_shell *shell, int *ret)
{
	int		index;

	index = -1;
	while (shell->command[++index] && ft_strcmp(shell->command[index], ")"))
		;
	if (shell->command[index] && !shell->flag)
	{
		free(shell->command[index]);
		shell->command[index] = NULL;
		shell->mode = 1;
		return (0);
	}
	else if (shell->flag)
	{
		if (shell->lvl != 0)
			exit(*ret);
		return (1);
	}
	else
	{
		shell->mode = 0;
		return (0);
	}
}

// void	delete_brackets(t_shell *shell)
// {
// 	int		begin;
// 	int		end;
	
// 	begin = 0;
	
// 	while (begin < end)
// 	{
		
// 	}
// }

int		brackets_treatment(t_shell *shell, int *ret)
{
	int		tmp;

	// delete_brackets(shell);
	while (1)
	{
		if (ft_strcmp(shell->command[0], "("))
			return (command_found(shell, ret));
		else
		{
			if ((tmp = open_bracket_found(shell, ret)) == 0)
				return (0);
			else if (tmp == 1)
				return (1);
		}
	}
}
