/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_treatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:04:25 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/27 18:00:31 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>

int		find_brackets(char ***args, int *forks)
{
	int		index;
	int		commands;

	index = -1;
	commands = 0;
	*forks = 0;
	while ((*args)[++index])
		if (!ft_strcmp((*args)[index], "("))
			(*forks)++;
		else if (!ft_strcmp((*args)[index], ")"))
			(*forks)--;
		else
			commands++;
	if (!(*args = (char**)malloc(sizeof(char*) * (commands + 1))))
		return (12);
	return (0);
}

int		do_fork(pid_t *pid)
{
	int		ret;
	int		status;

	*pid = fork();
	if (*pid > 0)
	{
		if ((waitpid(*pid, &status, WUNTRACED) == -1))
			error_print_return(NULL);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			if ((waitpid(*pid, &status, WUNTRACED) == -1))
				error_print_return(NULL);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				ret = 130;
			if (WTERMSIG(status) == 3)
				ret = 131;
		}
		else
			ret = WEXITSTATUS(status);
	}
	return (0);
}

int		do_forks(int forks, int *flag, pid_t *pid)
{
	if (forks > 0)
	{
		*flag = 0;
		while (forks--)
			return (do_fork(pid));
	}
	else if (forks < 0)
		*flag = 1;
	else
	{
		*flag = 1;
			return (do_fork(pid));
	}
	return (0);
}

int		brackets_treatment(char ***args, int *flag, pid_t *pid)
{
	char	**link;
	int		forks;
	int		sindex;
	int		index;
	
	link = *args;
	if (find_brackets(args, &forks))
		return (12);
	index = -1;
	sindex = -1;
	while (link[++index])
		if (ft_strcmp(link[index], "(") && ft_strcmp(link[index], ")"))
			(*args)[++sindex] = link[index];
	(*args)[++sindex] = NULL;
	return (do_forks(forks, flag, pid));
}
