/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_treatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:04:25 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/27 19:13:41 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		do_fork(void)
{
	pid_t	pid;
	int		ret;
	int		status;

	pid = fork();
	if (pid > 0)
		return (-(int)pid);
	return (0);
}

int		do_forks(int forks, int *flag)
{
	if (forks > 0)
	{
		*flag = 0;
		while (forks--)
			return (do_fork());
	}
	else if (forks < 0)
	{
		*flag = 1;
		return (0);
	}
	else
	{
		*flag = 1;
		return (do_fork());
	}
}

int		find_brackets(char ***args, int *forks, int *brackets)
{
	int		index;
	int		commands;

	index = -1;
	commands = 0;
	*forks = 0;
	*brackets = 0;
	while ((*args)[++index])
		if (!ft_strcmp((*args)[index], "("))
		{
			(*forks)++;
			*brackets = 1;
		}
		else if (!ft_strcmp((*args)[index], ")"))
		{
			(*forks)--;
			*brackets = 1;
		}
		else
			commands++;
	if ((*brackets) == 0)
		return (0);
	if (!(*args = (char**)malloc(sizeof(char*) * (commands + 1))))
		return (12);
	return (0);
}

int		brackets_treatment(char ***args, int *flag)
{
	char	**link;
	int		forks;
	int		sindex;
	int		index;
	int		brackets;
	
	link = *args;
	if (find_brackets(args, &forks, &brackets))
		return (12);
	if (!brackets)
		return (0);
	index = -1;
	sindex = -1;
	while (link[++index])
		if (ft_strcmp(link[index], "(") && ft_strcmp(link[index], ")"))
			(*args)[++sindex] = link[index];
	(*args)[++sindex] = NULL;
	return (do_forks(forks, flag));
}
