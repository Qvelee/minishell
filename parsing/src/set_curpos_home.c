/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_curpos_home.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:01:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:24:32 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "termcap.h"
#include "get_static.h"

int	set_curpos_home(char *start, char *end)
{
	int len;
	int res;

	len = ft_substrlen(start, end);
	if (len > 0)
	{
		tputs(tgoto(tgetstr("ch", 0), 0, MSH), 1, ft_putchar);
		get_cursor()->x = MSH + 1;
		if ((res = (len + MSH) / get_term_size().x) != 0)
			tputs(tgoto(tgetstr("UP", NULL), 0, res), 0, ft_putchar);
		get_cursor()->y -= res;
	}
	return (1);
}
