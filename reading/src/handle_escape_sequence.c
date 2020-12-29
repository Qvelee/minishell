/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:19:22 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/29 04:43:01 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term.h"
#include "structs.h"
#include "get_static.h"
#include "ft_readline.h"

void	backspace(char **str, int *i, int len, t_coor term)
{
	if (get_cursor()->x == 1)
	{
		get_cursor()->x = get_term_size().x;
		get_cursor()->y--;
		tputs(cursor_up, 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", 0), 0, term.x), 1, ft_putchar);
	}
	else
	{
		tputs(cursor_left, 1, ft_putchar);
		get_cursor()->x--;
	}
	tputs(save_cursor, 1, ft_putchar);
	write(1, &(*str)[*i], len - *i);
	write(1, " ", 1);
	tputs(tigetstr("ed"), 1, ft_putchar);
	tputs(restore_cursor, 1, ft_putchar);
	term.y = 1 + ((*str)[*i - 1] < 0);
	ft_memmove((*str) + *i - term.y, (*str) + *i, len - *i + term.y);
	*i = *i - term.y;
	(*str)[len - term.y] = 0;
}

void	delete(char **str, int *i, int len)
{
	if ((*str)[*i] < 0)
		ft_memmove((*str) + *i, (*str) + *i + 2, len - *i);
	else
		ft_memmove((*str) + *i, (*str) + *i + 1, len - *i);
	(*str)[len] = 0;
	tputs(save_cursor, 1, ft_putchar);
	write(1, &(*str)[*i], len - *i);
	write(1, " ", 1);
	tputs(tigetstr("ed"), 1, ft_putchar);
	tputs(restore_cursor, 1, ft_putchar);
}

void	copy_paste(char *c, char **str)
{
	if (*c == 21)
	{
		free(*c_str());
		*c_str() = ft_strdup(*str);
	}
	else if (*c == 25 && *c_str())
	{
		realloc_str(ft_strlen(*c_str()));
		handle_chars(g_line()->str, *c_str(), g_line()->i, ft_strlen(*c_str()));
	}
}

int		handle_escape_sequence(char *c, char *(*str), int *i, t_history **his)
{
	int		len;
	t_coor	term;
	int		lc;

	lc = ft_strlen(c);
	len = ft_strlen((*str));
	term = get_term_size();
	tputs(cursor_invisible, 1, ft_putchar);
	check_arrows(c, str, i, his);
	check_ctrl(c, str, i, lc);
	if (!ft_memcmp("\v", c, lc + 1))
	{
		tputs(tigetstr("ed"), 1, ft_putchar);
		(*str)[*i] = 0;
	}
	else if (*i < len && !ft_memcmp(tgetstr("kD", 0), c, lc + 1))
		delete(str, i, len);
	else if (*i > 0 && (!ft_memcmp(key_backspace, c, lc + 1) || *c == '\177'))
		backspace(str, i, len, term);
	copy_paste(c, str);
	tputs(cursor_visible, 1, ft_putchar);
	tputs(cursor_normal, 1, ft_putchar);
	return (0);
}
