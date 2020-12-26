/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:03:59 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/26 13:07:28 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "structs.h"
#include "executor.h"

void	free_matrix(char **matrix)
{
	int		index;

	index = -1;
	if (matrix)
	{
		while (matrix[++index])
			free(matrix[index]);
		free(matrix);
	}
}

void	exit_minishell(int code, char **args, t_envp **envp_list)
{
	free_matrix(args);
	envp_lst_clear(envp_list, free);
	exit(code);
}
