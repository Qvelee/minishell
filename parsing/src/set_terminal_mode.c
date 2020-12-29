/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:35:36 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/28 19:23:37 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "structs.h"
#include "termcap.h"

#if BONUS

int	set_terminal_mode2(void)
{
	t_term	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ISIG);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

int	set_terminal_mode(char *term_name)
{
	t_term	term;
	
	if (!term_name)
		term_name = "xterm-256color";
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag |= (ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	if (tgetent(0, term_name) == -1)
		return (-1);
	return (1);
}

int	remove_terminal_mode(void)
{
	t_term term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= (ICANON);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

#else

int	set_terminal_mode(char __attribute__((unused)) *term_name)
{
	return (0);
}

int	remove_terminal_mode(void)
{
	return (0);
}

int	set_terminal_mode2(void)
{
	return (0);
}
#endif