/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:58:23 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/21 17:21:04 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int		error_arg_export(char *argument)
{
	write(2, "minishell: export: `", 20);
	write(2, argument, ft_strlen(argument));
	write(2, "\': Not a valid identifier\n", 26);
	return (1);
}

void		print_line(char *line)
{
	int		index;

	index = -1;
	write(1, "declare -x ", 11);
	while (line[++index] != '=' && line[index] != '\0')
		write(1, &line[index], 1);
	if (ft_strchr(line, '='))
	{
		write(1, "=\"", 2);
		index ++;
	}
	while (line[index] != '\0')
		write(1, &line[index++], 1);
	if (ft_strchr(line, '='))
		write(1, "\"", 1);
	write(1, "\n", 1);
}
