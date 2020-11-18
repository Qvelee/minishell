/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequance.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:19:22 by sgertrud          #+#    #+#             */
/*   Updated: 2020/11/17 20:23:05 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "main.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
}

int	handle_escape_sequance(char *command,t_envp *envp)
{
	/*char *term_name;
	char *str;
	term_name = envp_get_var_value(envp,"TERM");
	tgetent(0,term_name);
	str = tgetstr("le", 0);
	write(1,"lalsa",5);
	tputs(str,1,ft_putchar);*/
	return(0);
}