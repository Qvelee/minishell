/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 10:28:59 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/30 09:20:01 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term.h"
#include "structs.h"
#include "get_static.h"
#include "sys/ioctl.h"
#include "executor_external.h"
#include "ft_readline.h"

void	move_rest(char *str, size_t i, int ret)
{
	size_t len;

	tputs(cursor_invisible, 1, ft_putchar);
	len = ft_strlen(str);
	if (len > i)
	{
		write(1, &str[i], len - i);
		tputs(tgoto(tgetstr("ch", 0), 0, get_cursor()->x - 1), 1, ft_putchar);
		cursor_dec(&str[i], &str[len - 1]);
		ft_memmove(&str[i + ret], &str[i], len - i);
		str[len + ret] = 0;
	}
	tputs(cursor_visible, 1, ft_putchar);
	tputs(cursor_normal, 1, ft_putchar);
}

void	handle_chars(char *str, char *sym, size_t *i, int ret)
{
	size_t len;
	size_t j;

	write(1, sym, ret);
	len = ft_strlen_term(sym);
	if ((get_cursor()->x == get_term_size().x && (ret == 1 ||
	(ret == 2 && sym[0] < 0))) || ((len + get_cursor()->x) %
	get_term_size().x == 1))
	{
		write(1, " ", 1);
		tputs(cursor_left, 1, ft_putchar);
	}
	cursor_inc(get_cursor(), len);
	j = 0;
	if (str[*i])
		move_rest(str, *i, ret);
	else
		str[*i + ret] = 0;
	while (j < (size_t)ret)
		str[(*i)++] = sym[j++];
}

void	move_to_out(char *str, int fd, size_t i)
{
	size_t len;
	size_t j;

	len = ft_strlen(str);
	str[len] = '\n';
	str[len + 1] = 0;
	if (*str && *str != '\n' && fd > 0)
		write(fd, str, ft_strlen(str));
	write(1, "\n", 1);
	j = (ft_substrlen(str, &str[i]) + MSH) / get_term_size().x;
	len = (ft_substrlen(str, &str[len - 1]) + MSH) / get_term_size().x;
	while (j++ < len && len)
		write(1, "\n", 1);
}

char	*read_one_sym(int *ret)
{
	char	buff[BUFF_SIZE];
	int		n;
	int		out;
	char	*sym;

	sym = 0;
	*ret = 0;
	out = read(0, buff, BUFF_SIZE - 1);
	*ret += out;
	buff[out] = 0;
	sym = join_free(sym, buff);
	while (ioctl(0, FIONREAD, &n) == 0 && n > 0)
	{
		out = read(0, buff, BUFF_SIZE - 1);
		*ret += out;
		buff[out] = 0;
		sym = join_free(sym, buff);
	}
	*ret = ft_strlen(sym);
	return (sym);
}

void	realloc_str(int ret)
{
	while ((int)ft_strlen(g_line()->str) + 1 + ret >= g_line()->size)
	{
		g_line()->str = ft_realloc_str(g_line()->str,
		g_line()->size, g_line()->size * 2 + 1);
		g_line()->size *= 2;
	}
}
