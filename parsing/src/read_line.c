/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:53:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/22 15:28:32 by sgertrud         ###   ########.fr       */
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
char	*read_line(t_envp *envp)
{
	tputs(tgetstr("ML",0),1,ft_putchar);
	int fd;
	int ret;
	char sym[2048];
	t_history *history;
	int i;
	int len;
	int j;
	int k;
	int last_cursor;
	int *lens;
	char *str;
	char buff[BUFF_SIZE] = {0};
	t_coor cursor;
	ret = 1;
	k = 1;
	sym[0] = 0;
	str = ft_calloc(1,BUFF_SIZE);
	i = 0;
		//refresh();
	fd = open(envp_get_var_value(envp,"HISTFILE"),O_CREAT| O_RDWR | O_APPEND, 0666);
//	char *debug = tgetstr("wi", 0);
	//int debug2 = getcurx(curscr);
	//printf("%d\n",debug2 );
	//getyx(stdscr,(savecursor()->y),(savecursor()->x));
	//wmove(curscr,30,30);
//	move(30,30);
	//wrefresh(curscr);
	*savecursor() = get_cursor();
	//char *debug = cursor_address;
	//tputs(save_cursor, 1, ft_putchar);
		history = 0;
	if (fd > 0)
		history = read_history(fd);
	*get_line() = (t_line){&str,&i,0};
	history = add_history(history,ft_strdup(str));
	ret = read(0, sym, 2048);
	while (sym[0] != 10 && sym[0] != 13)
	{
		if ((int)ft_strlen(str) + ret >= BUFF_SIZE * k)
		{
			str = ft_strjoin_gnl(str,buff);
			k++;
		}
		sym[ret] = 0;
		if (((sym[0] > 0 && sym[0] <= 31) || sym[0] == 127) && sym[0] != 4)
		{
			handle_escape_sequence(sym,envp, str,&i,&history);
		}
		else
		{

			j = 0;
			last_cursor = get_cursor().x;
			write(1, sym, ret);
			cursor = get_cursor();
			if (get_cursor().x > get_term_size().x || last_cursor == get_cursor().x)
			{
				tputs(tgoto(tigetstr("ind"), 0, get_cursor().y), 1, ft_putchar);
				//tputs(tgetstr("ho", 0), 1, ft_putchar);
			}
			if (str[i])
				{
					tputs(cursor_invisible, 1, ft_putchar);
					len = ft_strlen(str);
					tputs(save_cursor, 1, ft_putchar);
					//tputs(tgoto(tgetstr("ce", 0),len - *i + 1,0),1,ft_putchar);
					write(1, &str[i],len - i);
					/*if (get_cursor().x > get_term_size().x)
					{
						tputs(tgoto(tigetstr("ind"), 0, get_cursor().y), 1, ft_putchar);
					}*/
					tputs(tigetstr("ed"), 1, ft_putchar);
					tputs(restore_cursor, 1, ft_putchar);
					while (--len >= i - ret)
					str[len + ret + 1] = str[len + 1];
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

		ret = read(0, sym, 2048);

	}
	if	(str && *str != 4)
	{
		len = ft_strlen(str);
		str[len] = '\n';
		str[len + 1] = 0;
		if (*str && *str != '\n' && fd > 0)
		{
			write(fd,str,ft_strlen(str));
			//write(fd, "\n", 1);
		}
		//i = get_cursor().x;
		write(1,"\n", 1);
		j = (ft_substrlen(str,&str[i]) + MSH) / get_term_size().x;
		len = (ft_substrlen(str,&str[len - 1]) + MSH)  / get_term_size().x;
		while (j++ < len && len)
			write(1, "\n", 1);
	}
	if (fd > 0)
		close(fd);
	free_history(history);
	return (str);
}