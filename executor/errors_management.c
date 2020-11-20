/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:39:11 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/20 18:16:53 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
