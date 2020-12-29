/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_terminal_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 04:50:58 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/29 04:52:08 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "structs.h"
#include "termcap.h"
#if BONUS

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

int	remove_terminal_mode(void)
{
	return (0);
}

#endif
