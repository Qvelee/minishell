/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 10:28:59 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:19:14 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term.h"
#include "structs.h"
#include "parse_internal.h"
#include "get_static.h"
#include "sys/ioctl.h"
#include "executor_external.h"

void	move_rest(char *str, int i, int ret)
{
	int len;

	tputs(cursor_invisible, 1, ft_putchar);
	len = ft_strlen(str);
	write(1, &str[i], len - i);
	tputs(tgoto(tgetstr("ch", 0), 0, get_cursor()->x - 1), 1, ft_putchar);
	cursor_dec(&str[i], &str[len - 1]);
	ft_memmove(&str[i + ret], &str[i], len - i);
	str[len + ret] = 0;
	tputs(cursor_visible, 1, ft_putchar);
}

void	handle_chars(char *str, char *sym, int *i, int ret)
{
	int len;
	int j;

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
	while (j < ret)
		str[(*i)++] = sym[j++];
}

void	move_to_out(char *str, int fd, int i)
{
	int len;
	int j;

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
	sym = ft_strjoin_gnl(sym, buff);
	while (ioctl(0, FIONREAD, &n) == 0 && n > 0)
	{
		out = read(0, buff, BUFF_SIZE - 1);
		*ret += out;
		buff[out] = 0;
		sym = ft_strjoin_gnl(sym, buff);
	}
	*ret = ft_strlen(sym);
	return (sym);
}

void	handle_one_sym(int ret, t_history *history, int *i, t_envp *envp)
{
	char *sym;

	sym = read_one_sym(&ret);
	while (sym[0] != 10 && sym[0] != 13 && sym[0] != 3 && !(sym[ret] = 0))
	{
		if (!get_line()->str[0] && sym[0] == 4)
			do_command((char *[2]){ft_strdup("exit"), 0}, &envp);
		if (sym[0] != 4 && (get_line()->sig = 10))
		{
			while ((int)ft_strlen(get_line()->str) + 1 + ret >=
			get_line()->size)
			{
				get_line()->str = ft_realloc_str(get_line()->str,
				get_line()->size, get_line()->size * 2);
				get_line()->size *= 2;
			}
			if (((sym[0] > 0 && sym[0] <= 31) || sym[0] == 127) && sym[0] != 4)
				handle_escape_sequence(sym, &get_line()->str, i, &history);
			else
				handle_chars(get_line()->str, sym, i, ret);
			free(sym);
		}
		sym = read_one_sym(&ret);
	}
	free(sym);
}
