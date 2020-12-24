/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:28:30 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/22 20:33:45 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "sys/ioctl.h"
#include "main.h"
#include "libft.h"
#include "termcap.h"

t_coor get_term_size(void)
{
	t_coor coor;
	struct winsize win;

	//coor.x = tgetnum("co");
	//coor.y = tgetnum("li");
	ioctl(1,TIOCGWINSZ, &win);
	coor.x = win.ws_col;
	coor.y = win.ws_row;
	return(coor);
}

t_coor *get_cursor(void)
{
	static t_coor cursor;
	return (&cursor);
}