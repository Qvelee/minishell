/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slashes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 05:41:03 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 10:34:13 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "get_static.h"

void	remove_slashes(t_commands *c)
{
	int i;
	int j;
	int len;

	i = -1;
	j = 1;
	while (c->command[++i])
	{
		j = 1;
		len = ft_strlen(c->command[i]);
		while (c->command[i] && c->command[i][j - 1] && c->command[i][j])
		{
			if (check_sc(c->command[i][j]) &&
			c->command[i][j - 1] == '\\')
				ft_memmove(&c->command[i][j - 1],
				&c->command[i][j], len - j + 1);
			j++;
		}
		if (!c->command[i])
			break ;
	}
}
