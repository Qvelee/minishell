/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_treatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:24:33 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/09 19:38:13 by nelisabe         ###   ########.fr       */
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

	if (shell->flag)
	{
		shell->flag++;
		shell->command = &shell->command[1];
		return (2);
	}
	pid = fork();
	if (pid == 0)
	{
		shell->command = &shell->command[1];
		return (2);
	}
	else if (pid > 0)
		wait_subprocess(pid, ret);
	index = -1;
	while (shell->command[++index])
		if (!ft_strcmp(shell->command[index], "("))
			shell->flag++;
	index = -1;
	while (shell->command[++index] && ft_strcmp(shell->command[index], ")"))
		;
	if (shell->command[index])
	{
		shell->command = &shell->command[index + 1];
		shell->mode = 0;
		// if (shell->command[0])
		// 	exit(*ret);
		shell->flag = !shell->flag ? 0 : shell->flag - 1;
		return (0);
	}
	else
		return (1);
}

int		command_found(t_shell *shell)
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
		if (shell->command[index])
			shell->flag--;
		return (1);
	}
	else
	{
		shell->mode = 0;
		return (0);
	}
}

void	remove_excess_brackets(t_shell *shell, int open, int close)
{
	int		index;
	int		tmp_open;
	int		tmp_close;

	index = 0;
	tmp_open = open;
	tmp_close = close;
	while (shell->command[index] && \
		!ft_strcmp(shell->command[index], "(") && tmp_open-- && tmp_close--)
		index++;
	shell->command = &shell->command[index];
	index = 0;
	tmp_open = open;
	tmp_close = close;
	while (shell->command[index] && ft_strcmp(shell->command[index], ")"))
		index++;
	while (shell->command[++index] && tmp_open-- && tmp_close--)
		if (!ft_strcmp(shell->command[index], ")"))
		{
			free(shell->command[index]);
			shell->command[index] = NULL;
		}
}

void	delete_brackets(t_shell *shell)
{
	int		open;
	int		close;
	int		index;
	
	open = -1;
	close = -1;
	index = -1;
	while (shell->command[++index] && !ft_strcmp(shell->command[index], "("))
		open++;
	index = -1;
	while (shell->command[++index])
		;
	while (shell->command[--index] && !ft_strcmp(shell->command[index], ")"))
		close++;
	if (open != -1 && close != -1)
		remove_excess_brackets(shell, open, close);
}

int		brackets_treatment(t_shell *shell, int *ret)
{
	int		tmp;

	delete_brackets(shell);
	while (1)
	{
		if (ft_strcmp(shell->command[0], "("))
			return (command_found(shell));
		else
		{
			if ((tmp = open_bracket_found(shell, ret)) == 0)
				return (0);
			else if (tmp == 1)
				return (1);
		}
	}
}
