/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 14:03:14 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/09 14:27:48 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	init_sim_comm(int *index, int *fd, char ***simple_command, \
							int bytes)
{
	*index = 0;
	fd[0] = 0;
	fd[1] = 0;
	if (!(*simple_command = (char**)malloc(sizeof(char*) * bytes)))
		return (12);
	return (0);
}

static int	redirection(char *argument, char *value, \
								int *fd, t_envp *envp)
{
	if (!ft_strcmp(argument, ">"))
		return (redirect_output(value, &fd[0], 1));
	if (!ft_strcmp(argument, ">>"))
		return (redirect_output(value, &fd[0], 2));
	if (!ft_strcmp(argument, "<"))
		return (redirect_input(value, &fd[1], 1, envp));
	if (!ft_strcmp(argument, "<<"))
		return (redirect_input(value, &fd[1], 2, envp));
	return (-1);
}

static int	create_simple_command(t_commands **commands, char **args, \
									int *buff, t_envp *envp)
{
	t_commands	*command;
	char		**simple_command;
	int			fd[2];
	int			index;
	int			ret;

	if (init_sim_comm(&index, fd, &simple_command, buff[0] - buff[1] + 1))
		return (error_print_return(NULL));
	while (buff[1] < buff[0])
	{
		if ((ret = redirection(args[buff[1]], args[buff[1] + 1], \
								fd, envp)) == -1)
			simple_command[index++] = args[buff[1]++];
		else if (ret == 0)
			buff[1] += 2;
		else if (check_fatal_error(ret))
			return (comm_return_int(ret, simple_command));
		else
			break ;
	}
	simple_command[index] = NULL;
	if (!(command = comm_lst_new(simple_command, fd[0], fd[1])))
		return (comm_return_int(error_print_return(NULL), simple_command));
	comm_add_back(command, commands);
	return (0);
}

static int	cut_to_simple_commands(char **args, t_commands **commands, t_envp *envp)
{
	t_commands	*command;
	int			index;
	int			start;
	int			buff[2];
	int			ret;

	*commands = NULL;
	start = 0;
	index = -1;
	while (args[++index])
		if (!ft_strcmp(args[index], "|"))
		{
			buff[0] = index;
			buff[1] = start;
			if ((ret = create_simple_command(commands, args, buff, envp)))
				return (ret);
			start = index + 1;
		}
	buff[0] = index;
	buff[1] = start;
	if ((ret = create_simple_command(commands, args, buff, envp)))
		return (ret);
	return (0);
}

int			parse_command_ex(char **args, t_commands **commands, t_envp *envp)
{
	int		ret;

	if ((ret = cut_to_simple_commands(args, commands, envp)))
	{
		comm_lst_clr(commands);
		return (ret);
	}
	return (0);
}
