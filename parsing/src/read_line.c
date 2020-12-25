/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:53:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/24 14:12:50 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include "parse.h"
#include <stdlib.h>
#include "libft.h"
#include <term.h>
#include <fcntl.h>
#include "ncurses.h"
#include "curses.h"
#include "errno.h"
#include "sys/ioctl.h"

char *read_line(t_envp *envp)
{
	*(get_cursor()) = get_cursor_start();
	//printf("%d, %d",get_cursor()->x,get_cursor()->y);
	//tputs(tgetstr("ML",0),1,ft_putchar);
	int fd;
	int ret;
	//char sym[2048];
	char *sym;
	t_history *history;
	int i;
	int out;
	int len;
	int j;
	int k;
	int size;
	int last_cursor;
	int *lens;
	int n;
	char *str;
	char *histfile;
	//char size = BUFF_SIZE;
	sym = 0;
	size = BUFF_SIZE;
	char buff[BUFF_SIZE] = {0};
	t_coor cursor;
	ret = 1;
	k = 1;
	//sym[0] = 0;
	str = ft_calloc(1, BUFF_SIZE);
	str[0] = 0;
	i = 0;
	//refresh();
	fd = -1;
	if ((histfile = envp_get_var_value(envp, "HISTFILE")))
		fd = open(histfile, O_CREAT | O_RDWR | O_APPEND, 0666);
	//	char *debug = tgetstr("wi", 0);
	//int debug2 = getcurx(curscr);
	//printf("%d\n",debug2 );
	//getyx(stdscr,(savecursor()->y),(savecursor()->x));
	//wmove(curscr,30,30);
	//	move(30,30);
	//wrefresh(curscr);
	//	*savecursor() = get_cursor();
	//char *debug = cursor_address;
	//tputs(save_cursor, 1, ft_putchar);
	history = 0;
	if (fd > 0)
		history = read_history(fd);
	get_line()->str = &str;
	history = add_history(history, ft_strdup(str));
	out = read(0, buff, BUFF_SIZE - 1);
	/*while (out == 0)
	out = read(0, buff, BUFF_SIZE - 1);*/
	ret += out;
	buff[out] = 0;
	sym = ft_strjoin_gnl(sym, buff);
	while (ioctl(0, FIONREAD, &n) == 0 && n > 0)
	{
		out = read(0, buff, BUFF_SIZE - 1);
		ret += out;
		buff[out] = 0;
		sym = ft_strjoin_gnl(sym, buff);
	}

	//get_next_line(0,&sym);
	ret = ft_strlen(sym);
	while (sym[0] != 10 && sym[0] != 13)
	{
		while ((int)ft_strlen(str) + 1 + ret >= get_line()->size)
		{
			str = ft_realloc_str(str, get_line()->size, get_line()->size * 2);
			get_line()->size *= 2;
			//	printf("I'm IN\n");
		}
		//	sleep(1);

		sym[ret] = 0;
		if (((sym[0] > 0 && sym[0] <= 31) || sym[0] == 127) && sym[0] != 4)
		{
			tputs(cursor_invisible, 1, ft_putchar);
			handle_escape_sequence(sym, envp, &str, &i, &history);
			tputs(cursor_visible, 1, ft_putchar);
		}
		else
		{
			write(1, sym, ret);
			len = ft_strlen_term(sym);
			if ((get_cursor()->x == get_term_size().x && (ret == 1 || (ret == 2 && sym[0] < 0))) || ((len + get_cursor()->x) % get_term_size().x == 1))
				tputs(tgoto(tigetstr("ind"), 0, get_cursor()->y), 1, ft_putchar);

			cursor_inc(get_cursor(), len);
			/*			if (cursor->x + 1 > get_term_size().x)
		{
			cursor->x = 1;
			tputs(tgoto(tigetstr("ind"), 0, cursor->y), 1, ft_putchar);
			cursor->y++;
		}*/
			j = 0;
			/*		last_cursor = get_cursor().x;*/

			/*cursor = get_cursor();
			if (cursor.x > get_term_size().x || last_cursor == cursor.x)
			{
				tputs(tgoto(tigetstr("ind"), 0, cursor.y), 1, ft_putchar);
				//tputs(tgetstr("ho", 0), 1, ft_putchar);
			}*/
			if (str[i])
			{
				tputs(cursor_invisible, 1, ft_putchar);
				len = ft_strlen(str);
				/*savecursor() = *get_cursor();
										tputs(save_cursor, 1, ft_putchar);*/
				//tputs(tgoto(tgetstr("ce", 0),len - *i + 1,0),1,ft_putchar);

				/*if ((get_cursor()->x + write(1, &str[i],len - i)) % get_term_size().x == 1)
					{
						tputs(tgoto(tigetstr("ind"), 0, 1), 1, ft_putchar);
					}*/
				write(1, &str[i], len - i);
				tputs(tgoto(tgetstr("ch", 0), 0, get_cursor()->x - 1), 1, ft_putchar);
				/*if (!((get_cursor()->x + write(1, &str[i],len - i)) % get_term_size().x == 1))
								tputs(tigetstr("ed"), 1, ft_putchar);*/
				//tputs(tgoto(tigetstr("ind"), 0, 1), 1, ft_putchar);

				//tputs(restore_cursor, 1, ft_putchar);
				cursor_dec(&str[i], &str[len - 1]);
				ft_memmove(&str[i + ret], &str[i], len - i);
				str[len + ret] = 0;
				/*while (--len >= i - ret)
					str[len + ret + 1] = str[len + 1];*/
				tputs(cursor_visible, 1, ft_putchar);
			}
			else
			{
				str[i + ret] = 0;
			}
			while (j < ret)
			{
				str[i++] = sym[j++];
			}
		}
		if (*str == 4)
		{
			//free(str);
			//str = 0;
			break;
		}
		free(sym);
		sym = 0;
		ret = 0;
		out = read(0, buff, BUFF_SIZE - 1);
		/*while (out == 0)
	out = read(0, buff, BUFF_SIZE - 1);*/
		ret += out;
		buff[out] = 0;
		sym = ft_strjoin_gnl(sym, buff);
		while (ioctl(0, FIONREAD, &n) == 0 && n > 0)
		{
			out = read(0, buff, BUFF_SIZE - 1);
			ret += out;
			buff[out] = 0;
			sym = ft_strjoin_gnl(sym, buff);
		}
		if (get_line()->sig)
		{
			write(1, "\n", 1);
			j = (ft_substrlen(str, &str[i]) + MSH) / get_term_size().x;
			len = (ft_substrlen(str, &str[len - 1]) + MSH) / get_term_size().x;
			while (j++ < len && len)
				write(1, "\n", 1);
		}
	}
	//sleep(1);
	free(sym);
	sym = 0;
	if (str && *str != 4)
	{
		len = ft_strlen(str);
		str[len] = '\n';
		str[len + 1] = 0;
		if (*str && *str != '\n' && fd > 0)
		{
			write(fd, str, ft_strlen(str));
			//write(fd, "\n", 1);
		}
		//i = get_cursor().x;
		write(1, "\n", 1);
		j = (ft_substrlen(str, &str[i]) + MSH) / get_term_size().x;
		len = (ft_substrlen(str, &str[len - 1]) + MSH) / get_term_size().x;
		while (j++ < len && len)
			write(1, "\n", 1);
	}
	if (fd > 0)
		close(fd);
	free_history(history);
	return (str);
}