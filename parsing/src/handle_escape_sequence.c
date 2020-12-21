/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:19:22 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/21 02:46:43 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "main.h"
#include "libft.h"
#include <curses.h>
#include "parse.h"

int	ft_putchar(int c)
{
	return(write(1, &c, 1));
}


int	handle_escape_sequence(char *command, t_envp *envp, char *str, int *i,t_history **history)
{
	int len;
	t_coor cursor;
	t_coor term;

	len = ft_strlen(str);
	cursor = get_cursor();
	term = get_term_size();
	if (command[0] && command[1] && (command[2] == 'A' || command[2] == 'B' || command[2] == 'C' || command[2] == 'D'))
		command[1] = 'O';
	int j = 0;

	if ( !ft_memcmp(tigetstr("kUP5"),command,ft_strlen(command) + 1))
	{
		tputs(cursor_up, 1, ft_putchar);
	}
	//tputs(tgetstr("ei",0),1,&ft_putchar);
	if ( !ft_memcmp(key_up,command,ft_strlen(command) + 1) && (*history)->prev)
	{
		//if (*str)
		//{
			//*history = add_history(*history, str);
			(*history) = (*history)->prev;
	//	}
		//char *debug = tgetstr("u7", 0);
		set_curpos(str, &(str[*i]));
		//tputs(tgoto(tgetstr("cm", 0),savecursor()->x - 1,savecursor()->y -1), 1, ft_putchar);
		//tputs(restore_cursor, 1, ft_putchar);
		//tputs(cursor_home,1,ft_putchar);
		write(1, (*history)->str, ft_strlen((*history)->str));
		ft_strlcpy(str,(*history)->str, ft_strlen((*history)->str) + 1);
		tputs(tigetstr("ed"), 1, ft_putchar);
		*i = ft_strlen(str);

	}
	if ( !ft_memcmp(key_down,command,ft_strlen(command) + 1) && (*history)->next)
	{
		/*if (*str)
		*history = add_history(*history, str);*/
		(*history) = (*history)->next;
		//tputs(carriage_return, 1, ft_putchar);
		//tputs(restore_cursor, 1, ft_putchar);
		set_curpos(str, &(str[*i]));
		//char *debug = tgoto(tgetstr("CM", 0),savecursor()->x - 1,savecursor()->y - 1);
		//tputs(tgoto(tgetstr("cm", 0),savecursor()->x - 1,savecursor()->y - 1), 1, ft_putchar);
		write(1, (*history)->str, ft_strlen((*history)->str));
		ft_strlcpy(str,(*history)->str, ft_strlen((*history)->str) + 1);
		tputs(tigetstr("ed"), 1, ft_putchar);
		*i = ft_strlen(str);
	}
	if (*i > 0 && !ft_memcmp(tgetstr("kl", 0),command,ft_strlen(command) + 1))
	{
		if (cursor.x == 1)
		{

			tputs(tgetstr("up", 0), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", 0), 0, term.x),1,ft_putchar);
		}
		else
			tputs(tgetstr("le", 0),1,ft_putchar);
		if (str[*i - 1] < 0)
			(*i)--;
		(*i)--;
	}
	else if (*i < len && !ft_memcmp(tgetstr("kr", 0),command,ft_strlen(command)+ 1))
	{
		if (cursor.x == term.x)
		{

			tputs(cursor_down, 1, ft_putchar);
			tputs(carriage_return ,1,ft_putchar);
		}
		else
			tputs(tgetstr("nd", 0),1,ft_putchar);
		if (str[*i + 1] < 0)
			(*i)++;
		(*i)++;
	}
	else if (*i < len && !ft_memcmp(tgetstr("kD", 0),command,ft_strlen(command)+ 1))
	{
		if (str[*i] <  0)
			ft_memmove(str + *i,str + *i + 2, len - *i);
		else
			ft_memmove(str + *i,str + *i + 1, len - *i);
		str[len] = 0;
		char* debug = save_cursor;
		tputs(save_cursor, 1, ft_putchar);
		//tputs(tgoto(tgetstr("ce", 0),len - *i + 1,0),1,ft_putchar);
		write(1, &str[*i], len - *i);
		tputs(tigetstr("ed"), 1, ft_putchar);
		tputs(restore_cursor, 1, ft_putchar);
		//tputs(delete_character, 1, ft_putchar);
		//(*i)++;
	}
	else if (*i > 0 && !ft_memcmp(tgetstr("kb", 0),command,ft_strlen(command)+ 1))
	{
		if (cursor.x == 1)
		{

			tputs(tgetstr("up", 0), 1, ft_putchar);
			tputs(tgoto(tgetstr("ch", 0), 0, term.x),1,ft_putchar);
		}
		else
			tputs(tgetstr("le", 0),1,ft_putchar);
		//tputs(tgetstr("dc", 0),1,ft_putchar);
		char* debug = save_cursor;
		tputs("\e[s", 1, ft_putchar);
		//tputs(tgoto(tgetstr("ce", 0),len - *i + 1,0),1,ft_putchar);
		write(1, &str[*i], len - *i);
		tputs(tigetstr("ed"), 1, ft_putchar);
		tputs("\e[u", 1, ft_putchar);
		if (str[*i - 1] < 0)
		{
			ft_memmove(str + *i - 2,str + *i, len - *i + 2);
			*i = *i - 2;
			str[len - 2] = 0;
		}
		else
		{
			ft_memmove(str + *i - 1,str + *i, len - *i + 1);
			(*i)--;
			str[len - 1] = 0;
		}
	}
	//tputs(tgetstr("im",0),1,&ft_putchar);
	return(0);
}