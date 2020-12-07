/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:03:14 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/07 17:52:34 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int			init_sim_comm(int *index, int *fd, char ***simple_command, \
							int bytes)
{
	*index = 0;
	fd[0] = 0;
	fd[1] = 0;
	if (!(*simple_command = (char**)malloc(sizeof(char*) * bytes)))
		return (12);
	return (0);
}

int			redirection(char *argument, char *value, \
								int *fd_out, int *fd_in)
{
	if (!ft_strcmp(argument, ">"))
		return (redirect_output(value, fd_out, 1));
	if (!ft_strcmp(argument, ">>"))
		return (redirect_output(value, fd_out, 2));
	if (!ft_strcmp(argument, "<"))
		return (redirect_input(value, fd_in, 1));
	if (!ft_strcmp(argument, "<<"))
		return (redirect_input(value, fd_in, 2));
	return (-1);
}

int			create_simple_command(t_commands **commands, char **args, \
									int start, int end)
{
	t_commands	*command;
	char		**simple_command;
	int			fd[2];
	int			index;
	int			ret;

	if (init_sim_comm(&index, fd, &simple_command, end - start + 1))
		return (error_print_return(NULL));
	while (start < end)
	{
		if ((ret = redirection(args[start], args[start + 1], \
								&fd[0], &fd[1])) == -1)
			simple_command[index++] = args[start++];
		else if (ret == 0)
			start += 2;
		else if (ret < 0)
			return (comm_return_int(ret * -1, simple_command));
		else
			break ;
	}
	simple_command[index] = NULL;
	if (!(command = comm_lst_new(simple_command, fd[0], fd[1])))
		return (comm_return_int(error_print_return(NULL), simple_command));
	comm_add_back(command, commands);
	return (0);
}

int			cut_to_simple_commands(char **args, t_commands **commands)
{
	t_commands	*command;
	int			index;
	int			start;
	int			ret;
	char		**simple_command;;

	index = -1;
	*commands = NULL;
	start = 0;
	while (args[++index])
		if (!ft_strcmp(args[index], "|"))
		{
			if ((ret = create_simple_command(commands, args, start, index)))
				return (ret);
			start = index + 1;
		}
	if ((ret = create_simple_command(commands, args, start, index)))
		return (ret);
	return (0);
}

int			parse_command_ex(char **args, t_commands **commands)
{
	int		ret;

	if ((ret = cut_to_simple_commands(args, commands)))
	{
		comm_lst_clr(commands);
		return (ret);
	}
	return (0);
}
