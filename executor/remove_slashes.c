/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slashes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 05:41:03 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 02:42:29 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "get_static.h"

void	remove_slashes(t_commands *commands)
{
	int i;
	int j;
	int len;

	i = -1;
	j = 1;
	while (commands->command[++i])
	{
		j = 1;
		len = ft_strlen(commands->command[i]);
		//commands->command[i] = replace_env(commands->command[i], *get_envp());
		//i = remake_args(commands->command, i);
		while (commands->command[i] && commands->command[i][j - 1] && commands->command[i][j])
		{
			if (check_sc(commands->command[i][j]) &&
			commands->command[i][j - 1] == '\\')
				ft_memmove(&commands->command[i][j - 1],
				&commands->command[i][j], len - j + 1);
			j++;
		}
		if (!commands->command[i])
			break ;
	}
}
