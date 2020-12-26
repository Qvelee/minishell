/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_curpos_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:01:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:24:46 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_static.h"
#include "termcap.h"

int	set_curpos_end(char *start, char *end)
{
	int len;
	int res;
	int len1;

	len1 = ft_strlen_term(start) + MSH;
	len = ft_substrlen(end, &start[ft_strlen(start)]);
	if (len > 0)
	{
		res = len1 % get_term_size().x;
		tputs(tgoto(tgetstr("ch", NULL), 1, res), 0, ft_putchar);
		get_cursor()->x = res + 1;
		len = len1 / get_term_size().x;
		res = ft_substrlen(start, end) / get_term_size().x;
		if (len > res)
			tputs(tgoto(tgetstr("DO", NULL), 0, len - res), 0, ft_putchar);
		get_cursor()->y -= (len - res);
	}
	return (1);
}
