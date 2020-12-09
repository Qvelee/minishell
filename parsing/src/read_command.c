/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:53:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/09 15:42:03 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include "parse.h"
#include <stdlib.h>
#include "libft.h"
#include <term.h>

char	*read_line(t_envp *envp)
{
	int ret;
	char sym[10];
	int i;
	int len;
	int j;
	int *lens;
	char *str;
	ret = 1;
	sym[0] = 0;
	str = ft_calloc(1,BUFF_SIZE);
	i = 0;
	ret = read(0, sym, 10);
	while (sym[0] != 10)
	{
		sym[ret] = 0;
		if (((sym[0] > 0 && sym[0] <= 31) || sym[0] == 127) && sym[0] != 4)
		{
			handle_escape_sequence(sym,envp, str,&i);
		}
		else
		{
			j = 0;
			if (str[i])
				{
					len = ft_strlen(str);
					while (--len > i - ret)
						str[len + ret] = str[len];
				}
			while (j < ret)
			{
				str[i++] = sym[j++];
			}
			write(1, sym,ret);

		}
		if (*str == 4)
		{
			//free(str);
			//str = 0;
			break;
		}
		ret = read(0, sym, 10);
	}
	if	(str && *str != 4)
	{
		str[ft_strlen(str)] = '\n';
		write(1, &(char){10}, 1);
	}
	return (str);
}