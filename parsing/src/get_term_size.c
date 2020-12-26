/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:28:30 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:22:48 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "sys/ioctl.h"

t_coor	get_term_size(void)
{
	t_coor			coor;
	struct winsize	win;

	ioctl(1, TIOCGWINSZ, &win);
	coor.x = win.ws_col;
	coor.y = win.ws_row;
	return (coor);
}

t_coor	*get_cursor(void)
{
	static	t_coor cursor;

	return (&cursor);
}
