/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_seqs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:06:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/28 09:56:03 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "get_static.h"
#include "term.h"
#include "libft.h"
#include "ft_readline.h"

void	go_right(char *str, int *i)
{
	t_coor	cursor;
	t_coor	term;
	int		len;

	cursor = *get_cursor();
	term = get_term_size();
	len = ft_strlen(str);
	if (*i < len)
	{
		if (cursor.x == term.x)
		{
			get_cursor()->x = 1;
			get_cursor()->y++;
			tputs(cursor_down, 1, ft_putchar);
			tputs(carriage_return, 1, ft_putchar);
		}
		else
		{
			get_cursor()->x++;
			tputs(cursor_right, 1, ft_putchar);
		}
		if (str[*i + 1] < 0)
			(*i)++;
		(*i)++;
	}
}

void	go_left(char *str, int *i)
{
	t_coor cursor;
	t_coor term;

	cursor = *get_cursor();
	term = get_term_size();
	if (*i > 0)
	{
		if (cursor.x == 1)
		{
			get_cursor()->x = term.x;
			get_cursor()->y--;
			tputs(cursor_up, 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", 0), 0, term.x), 1, ft_putchar);
		}
		else
		{
			tputs(cursor_left, 1, ft_putchar);
			get_cursor()->x--;
		}
		if (str[*i - 1] < 0)
			(*i)--;
		(*i)--;
	}
}

void	check_arrows(char *c, char **str, int *i, t_history **his)
{
	int len_c;
	int len;

	len_c = ft_strlen(c);
	len = ft_strlen(*str);
	if (c[0] && c[1] && (c[2] == 'A' || c[2] == 'B' ||
					c[2] == 'C' || c[2] == 'D' || c[2] == 'H' || c[2] == 'F'))
		c[1] = 'O';
	if (!ft_memcmp(key_up, c, len_c + 1) && (*his)->prev && (*his)->prev->str)
		history_up(his, str, i);
	if (!ft_memcmp(key_down, c, len_c + 1) && (*his)->next && (*his)->next->str)
		history_down(his, str, i);
	if (*i > 0 && !ft_memcmp(key_left, c, len_c + 1))
		go_left((*str), i);
	else if (*i < len && !ft_memcmp(key_right, c, len_c + 1))
		go_right((*str), i);
	if ((!ft_memcmp("\1", c, len_c + 1) || !ft_memcmp(key_home, c, len_c + 1))
	&& (set_curpos_home((*str), &((*str)[*i]))))
		*i = 0;
	if ((!ft_memcmp("\5", c, len_c + 1) || !ft_memcmp(key_end, c, len_c + 1))
	&& (set_curpos_end((*str), &((*str)[*i]))))
		*i = len;
}

void	check_ctrl(char *c, char **str, int *i, int len_c)
{
	t_coor	term;
	int		j;

	term = get_term_size();
	if (!(j = 0) && !ft_memcmp(tigetstr("kUP5"), c, len_c + 1))
		while (j++ < term.x)
			go_left((*str), i);
	if (!ft_memcmp(tigetstr("kDN5"), c, len_c + 1))
		while (j++ < term.x)
			go_right((*str), i);
	if (!ft_memcmp(tigetstr("kLFT5"), c, len_c + 1) && *i > 0)
	{
		while (*i > 0 && (*str)[*i - 1] == ' ')
			go_left((*str), i);
		while (*i > 0 && (*str)[*i - 1] != ' ')
			go_left((*str), i);
	}
	if (!ft_memcmp(tigetstr("kRIT5"), c, len_c + 1) &&
	*i < (int)ft_strlen((*str)))
	{
		while ((*str)[*i] == ' ' && *i < (int)ft_strlen((*str)))
			go_right((*str), i);
		while ((*str)[*i] != ' ' && *i < (int)ft_strlen((*str)))
			go_right((*str), i);
	}
}
