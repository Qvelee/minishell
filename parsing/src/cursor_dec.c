/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:42:17 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:26:00 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_static.h"
#include "termcap.h"

void	cursor_dec(char *start, char *end)
{
	int len;
	int len1;

	len1 = ft_substrlen(start, end);
	len = (get_cursor()->x + len1) / get_term_size().x;
	if ((get_cursor()->x + len1) % get_term_size().x == 0)
		len -= 1;
	if (len > 0)
		tputs(tgoto(tgetstr("UP", NULL), 0, len), 0, ft_putchar);
}
