/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_curpos_home.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:01:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/23 00:34:19 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "termcap.h"

void	set_curpos_home(char *start, char *end)
{
	int len;
	int res;
	int term;

	term = get_term_size().x;
	len = ft_substrlen(start, end);
	if (len > 0)
	{
		/*if ((res = len % get_term_size().x) >= term - MSH)
			tputs(tgoto(tgetstr("RI", NULL), 1 , get_term_size().x - res), 0, ft_putchar);
		else if (res > 0)
			tputs(tgoto(tgetstr("LE", NULL), 1 , res), 0, ft_putchar);*/
		tputs(tgoto(tgetstr("ch",0),0,MSH),1, ft_putchar);
		get_cursor()->x = MSH + 1;

		if ((res = (len + MSH) / get_term_size().x) != 0)
			tputs(tgoto(tgetstr("UP", NULL), 0 , res), 0, ft_putchar);
		get_cursor()->y -= res;
	}
}