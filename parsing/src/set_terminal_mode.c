/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:35:36 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:22:07 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "structs.h"
#include "termcap.h"

int	set_terminal_mode(char *term_name)
{
	t_term	term;
	char	buffer[1024];

	if (!term_name)
		term_name = "xterm-256color";
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	if (tgetent(buffer, term_name) == -1)
		return (-1);
	return (1);
}
