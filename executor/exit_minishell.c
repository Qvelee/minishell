/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:03:59 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/10 13:57:56 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
