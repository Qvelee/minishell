/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_inc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 20:35:43 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/24 06:25:30 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "termcap.h"
#include "term.h"

void cursor_inc(t_coor *cursor, int len)
{
	int i;
	t_coor buff;

	i = 0;

	buff.y = cursor->y;
	buff.x = (cursor->x + len) % get_term_size().x ;
	if (!buff.x)
	{
		buff.x = get_term_size().x;
		buff.y -= 1;
	}
	buff.y += (cursor->x + len) / get_term_size().x;
	*cursor = buff;
	/*while (i < len)
	{
		i++;
		if (cursor->x + 1 >= get_term_size().x)
		{
			cursor->x = 1;
			cursor->y++;
		}
		else
			cursor->x++;
	}*/
	/*if ((len + MSH) % get_term_size().x == 0)
		tputs(tgoto(tigetstr("ind"), 0, cursor->y), 1, ft_putchar);*/
}