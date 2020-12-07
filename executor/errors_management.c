/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:39:11 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/07 19:19:49 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int 	check_fatal_error(int code)
{
	const int	errors[10] = {5, 9, 11, 12, 14, 23, 24, 28, 77, 121};
	int			index;

	index = -1;
	while (++index < 10)
		if (code == errors[index])
			break ;
	if (index == 10)
		return (0);
	return (code);
}

void	exit_fatal(int code, char **args, t_envp **envp_list)
{
	free_matrix(args);
	envp_lst_clear(envp_list, free);
	remove_terminal_mode();
	exit(code);
}

int		error_command_not_found(char *command)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	return (127);
}

int		error_print_return(char *message)
{
	char	*error;

	error = strerror(errno);
	write(2, "minishell: ", 11);
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, ": ", 2);
	}
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (errno);
}

int		error_return_int(int return_value, char *memory_1, char *memory_2, \
	char **matrix)
{
	if (memory_1)
		free(memory_1);
	if (memory_2)
		free(memory_1);
	if (matrix)
		free_matrix(matrix);
	return (return_value);
}
