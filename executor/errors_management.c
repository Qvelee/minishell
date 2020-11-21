/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:39:11 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/21 14:37:44 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	check_memory_error(int code, char **args, t_envp **envp_list, \
	t_term term)
{
	if (code != 12)
		return ;
	free_matrix(args);
	envp_lst_clear(envp_list, free);
	remove_terminal_mode(term);
	write(2, "minishell: out of memory", 24);
	exit(12);
}

int		error_command_not_found(char *command)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, "command not found\n", 18);
	return (127);
}

int		error_print_return(char *massage)
{
	char	*error;

	if (!(error = strerror(errno)))
		return (12);
	else
	{
		write(2, massage, ft_strlen(massage));
		write(2, ": ", 2);
		write(2, error, ft_strlen(massage));
		write(2, "\n", 1);
	}
	return (errno);
}

char	*error_return_char(char *memory_1, char *memory_2, char **matrix)
{
	if (memory_1)
		free(memory_1);
	if (memory_2)
		free(memory_1);
	if (matrix)
		free_matrix(matrix);
	return (NULL);
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
