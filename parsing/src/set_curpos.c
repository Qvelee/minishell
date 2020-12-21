/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_curpos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:01:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/20 02:54:12 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "termcap.h"

void	set_curpos(char *start, char *end)
{
	int len;
	int res;

	len = ft_substrlen(start, end);
	if (len > 0)
	{
		if ((res = len % get_term_size().x) >= get_term_size().x - MSH)
			tputs(tgoto(tgetstr("RI", NULL), 1 , get_term_size().x - res), 0, ft_putchar);
		else if (res > 0)
			tputs(tgoto(tgetstr("LE", NULL), 1 , res), 0, ft_putchar);
		if ((res = (len + MSH) / get_term_size().x) != 0)
			tputs(tgoto(tgetstr("UP", NULL), 0 , res), 0, ft_putchar);
	}
}