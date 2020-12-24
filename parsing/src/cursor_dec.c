/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:42:17 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/24 00:30:22 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "termcap.h"

void	cursor_dec(char *start, char *end)
{;
/*	int res;
	int term;

	term = get_term_size().x;
	if (len > 0)
	{
		if ((res = len % get_term_size().x) >= term - MSH)
			tputs(tgoto(tgetstr("RI", NULL), 1 , get_term_size().x - res), 0, ft_putchar);
		else if (res > 0)
			tputs(tgoto(tgetstr("LE", NULL), 1 , res), 0, ft_putchar);*/
	/*	tputs(tgoto(tgetstr("ch",0),0,MSH),1, ft_putchar);
		get_cursor()->x = MSH + 1;

		if ((res = (len + MSH) / get_term_size().x) != 0)
			tputs(tgoto(tgetstr("UP", NULL), 0 , res), 0, ft_putchar);

		get_cursor()->y -= res;
	}*/
	int len;
	int res;
	int len1;
	int term;

	term = get_term_size().x;
	len1 = ft_substrlen(start,end);
	len = (get_cursor()->x + len1) / get_term_size().x;
	if ((get_cursor()->x + len1) % get_term_size().x == 0)
		len -= 1;
	//len1 = ft_strlen_term(start) + MSH;
//	len = ft_substrlen(end,&start[ft_strlen(start)]);
	if (len > 0)
	{
		/*res = len1 % get_term_size().x;
		tputs(tgoto(tgetstr("ch", NULL), 1 , res), 0, ft_putchar);
		get_cursor()->x = res + 1;*/
	//	len = (ft_strlen_term(start) + MSH) / get_term_size().x;
	//	res = ft_substrlen(start, end) / get_term_size().x;

	/*	else if (res > 0)
			tputs(tgoto(tgetstr("LE", NULL), 1 , res), 0, ft_putchar);*/
		/*if ((res = (len + MSH) / get_term_size().x) != 0)
			tputs(tgoto(tgetstr("DO", NULL), 0 , res), 0, ft_putchar);*/

		//if (len > res)
			tputs(tgoto(tgetstr("UP", NULL), 0 ,len) , 0, ft_putchar);
		//get_cursor()->y -= (len - res);
	}
}