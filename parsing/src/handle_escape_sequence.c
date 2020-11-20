/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_escape_sequence.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:19:22 by sgertrud          #+#    #+#             */
/*   Updated: 2020/11/20 16:49:44 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "main.h"
#include "libft.h"
#include <curses.h>

int	ft_putchar(int c)
{
	return(write(1, &c, 1));
}

int	handle_escape_sequence(char *command, t_envp *envp, char *str, int *i)
{
	int len;

	len = ft_strlen(str);
	char *term_name;
	if (command[0] && command[1] && (command[2] == 'A' || command[2] == 'B' || command[2] == 'C' || command[2] == 'D'))
		command[1] = 'O';
	
	//tputs(tgetstr("ei",0),1,&ft_putchar);
	if (*i > 0 && !ft_memcmp(tgetstr("kl", 0),command,ft_strlen(command) + 1))
	{
		tputs(tgetstr("le", 0),1,ft_putchar);
		(*i)--;
	}
	else if (*i < len && !ft_memcmp(tgetstr("kr", 0),command,ft_strlen(command)+ 1))
	{
		tputs(tgetstr("nd", 0),1,ft_putchar);
		(*i)++;
	}
	else if (*i < len && !ft_memcmp(tgetstr("kD", 0),command,ft_strlen(command)+ 1))
	{
		ft_memmove(str + *i,str + *i + 1, len - *i);
		str[len] = 0;
		tputs(tgetstr("dc", 0),1,ft_putchar);
		//(*i)++;
	}
	else if (*i > 0 && !ft_memcmp(tgetstr("kb", 0),command,ft_strlen(command)+ 1))
	{
		tputs(tgetstr("le", 0),1,ft_putchar);
		tputs(tgetstr("dc", 0),1,ft_putchar);
		ft_memmove(str + *i - 1,str + *i, len - *i + 1);
		str[len - 1] = 0;
		(*i)--;
	}
	//tputs(tgetstr("im",0),1,&ft_putchar);
	return(0);
}