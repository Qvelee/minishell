/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:10:57 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/02 19:56:58 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>

int			save_ret_value(int value, t_envp **envp_list)
{
	char	*value_to_save;
	char	*temp;

	if (!(temp = ft_itoa(value)))
		return (12);
	if (!(value_to_save = envp_create_envp_str("?", temp)))
	{
		free(temp);
		return (12);
	}
	free(temp);
	if (envp_replace_variable(envp_list, value_to_save, 0))
	{
		free(value_to_save);
		return (12);
	}
	return (0);
}

int			do_command(char **args, t_envp **envp_list, t_term term)
{
	int			return_value;
	t_commands	*commands;

	if (!(return_value = parse_command_ex(args, &commands)))
	{
		if ((return_value = run_commands(commands, envp_list, term)))
		{
			comm_lst_clr(&commands);
			check_memory_error(return_value, args, envp_list, term);
		}
	}
	else
		check_memory_error(return_value, args, envp_list, term);
	comm_lst_clr(&commands);
	if (save_ret_value(return_value, envp_list))
		check_memory_error(12, args, envp_list, term);
	return (return_value);
}
