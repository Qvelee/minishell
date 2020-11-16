/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:53:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/11/13 22:42:30 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include "parse.h"
#include <stdlib.h>

char	*read_line(struct termios term)
{
	int ret;
	char sym[10];
	int i;
	int j;
	char *str;
	ret = 1;
	sym[0] = 0;
	str = malloc(BUFF_SIZE);
	i = 0;
	while (sym[0] != 10)
	{
		ret = read(0, sym, 10);
		if (sym[0] == 27)
		{
			handle_escape_sequance(sym);
		/*	i = 0;
			while (i < ret)
			{
				printf("%d ", sym[i++]);
			}
			printf("\n");*/
		}
		else
		{
			j = 0;
			while (j < ret)
			{
				str[i++] = sym[j++];

			}
			write(1, sym,ret);
			//printf("this is char %d\n",*sym);
		}
	}
	return (str);
}