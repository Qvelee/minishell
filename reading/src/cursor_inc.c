/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_inc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 20:35:43 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:25:44 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "termcap.h"
#include "term.h"
#include "get_static.h"

void	cursor_inc(t_coor *cursor, int len)
{
	t_coor	buff;

	buff.y = cursor->y;
	buff.x = (cursor->x + len) % get_term_size().x;
	if (!buff.x)
	{
		buff.x = get_term_size().x;
		buff.y -= 1;
	}
	buff.y += (cursor->x + len) / get_term_size().x;
	*cursor = buff;
}
