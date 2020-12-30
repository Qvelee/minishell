/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:12:07 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/30 09:21:39 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "get_static.h"
#include "term.h"
#include "ft_readline.h"

void	history_down(t_history **history, char **str, size_t *i)
{
	size_t len;

	if ((*history)->next->str)
	{
		(*history) = (*history)->next;
		set_curpos_home((*str), &((*str)[*i]));
		write(1, (*history)->str, ft_strlen((*history)->str));
		len = ft_strlen_term((*history)->str);
		if ((len + get_cursor()->x) % get_term_size().x == 1)
		{
			write(1, " ", 1);
			tputs(cursor_left, 1, ft_putchar);
		}
		while ((int)ft_strlen((*history)->str) + 1 >= g_line()->size)
		{
			*str = ft_realloc_str(*str, g_line()->size, g_line()->size * 2 + 1);
			g_line()->size *= 2;
		}
		ft_strlcpy(*str, (*history)->str, ft_strlen((*history)->str) + 1);
		cursor_inc(get_cursor(), ft_strlen_term((*str)));
		if (get_cursor()->x != 1)
			tputs(tigetstr("ed"), 1, ft_putchar);
		*i = ft_strlen((*str));
	}
}

void	history_up(t_history **history, char **str, size_t *i)
{
	size_t len;

	if ((*history)->prev->str)
	{
		(*history) = (*history)->prev;
		set_curpos_home((*str), &((*str)[*i]));
		write(1, (*history)->str, ft_strlen((*history)->str));
		len = ft_strlen_term((*history)->str);
		if ((len + get_cursor()->x) % get_term_size().x == 1)
		{
			write(1, " ", 1);
			tputs(cursor_left, 1, ft_putchar);
		}
		while ((int)ft_strlen((*history)->str) + 1 >= g_line()->size)
		{
			*str = ft_realloc_str(*str, g_line()->size, g_line()->size * 2 + 1);
			g_line()->size *= 2;
		}
		ft_strlcpy(*str, (*history)->str, ft_strlen((*history)->str) + 1);
		cursor_inc(get_cursor(), ft_strlen_term((*str)));
		tputs(tigetstr("ed"), 1, ft_putchar);
		*i = ft_strlen((*str));
	}
}
