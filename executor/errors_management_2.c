/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:41:17 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/03 11:35:59 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		error_syntax(char symbol)
{
	write(2, "minishell: syntax error near unexpected token \'", 47);
	if (symbol == '\n')
		write(2, "newline", 7);
	else
		write(2, &symbol, 1);
	write(2, "\'\n", 2);
	return (2);
}

int		comm_error_return_int(int return_value, char **memory)
{
	if (memory)
		free(memory);
	return (return_value);
}
