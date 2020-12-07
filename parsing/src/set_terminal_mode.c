/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:35:36 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/07 18:30:25 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <term.h>
#include "parse.h"

int	set_terminal_mode(char *term_name)
{

	char *str;
	int a;
	t_term term;

	//a = tgetflag("es");
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	tgetent(0,term_name);
	tputs(enter_insert_mode,1,&ft_putchar);
	//tputs(tgetstr("ae",0),1,&ft_putchar);
	a = tgetnum("in");
	str = tgetstr("ic",0);
	//tputs(enter_blink_mode, 1, ft_putchar);
	//tputs(enter_delete_mode, 1, ft_putchar);
	return (1);
}
