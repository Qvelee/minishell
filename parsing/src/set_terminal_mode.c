/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:35:36 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/13 00:20:23 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
//#include <term.h>
#include "parse.h"
#include "termcap.h"

int	set_terminal_mode(char *term_name)
{
	if (!term_name)
		term_name = "xterm-256color";
	char *str;
	int a;
	t_term term;
	char buffer[1024];
	//a = tgetflag("es");
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);

	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	if (tgetent(buffer,term_name) == -1)
		return (-1);
	//tputs(enter_insert_mode,1,&ft_putchar);
	//tputs(tgetstr("ae",0),1,&ft_putchar);
	//a = tgetnum("in");
	//str = tigetstr("ed");
	//tputs(enter_blink_mode, 1, ft_putchar);
	//tputs(tigetstr("dm"), 1, ft_putchar);
	return (1);
}
