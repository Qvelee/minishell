/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:03:14 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/01 15:11:49 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char		**create_simple_command(char **args, int start, int index)
{
	char	**simple_command;
	int		sindex;

	simple_command = (char**)malloc(sizeof(char*) * ((index - start) + 1));
	sindex = 0;
	while (start < index)
	{
		simple_command[sindex] = args[start];
		sindex++;
		start++;
	}
	simple_command[sindex] = NULL;
	return (simple_command);
}

int			comm_cut_to_simple_commands(char **args, t_commands **commands)
{
	t_commands	*command;
	int			index;
	int			start;
	char		**simple_command;;

	index = -1;
	*commands = NULL;
	start = 0;
	while (args[++index])
		if (!ft_strcmp(args[index], "|"))
		{
			simple_command = create_simple_command(args, start, index);
			command = comm_lst_new(simple_command, -1, -1);
			comm_add_back(command, commands);
			start = index + 1;
		}
	simple_command = create_simple_command(args, start, index);
	command = comm_lst_new(simple_command, -1, -1);
	comm_add_back(command, commands);
	return (0);
}

int			parse_command_ex(char **args, t_commands **commands)
{
	t_commands	*temp;
	int			index;

	index = -1;
	comm_cut_to_simple_commands(args, commands);
	temp = *commands;
	return (0);
}
