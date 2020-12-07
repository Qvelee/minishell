/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:28:30 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/05 18:10:11 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "sys/ioctl.h"
#include "main.h"
#include "libft.h"
#include "termcap.h"

t_coor get_term_size(void)
{
	t_coor coor;
	coor.x = tgetnum("co");
	coor.y = tgetnum("li");
	//ioctl(1,TIOCGWINSZ, &coor);
	return(coor);
}

t_coor get_cursor(void)
{
	t_coor coor;
	char str[20];
	int i;

	i = 0;
	tputs("\E[6n", 1, ft_putchar);
	read(1, str, 20);
	while(!ft_isdigit(str[i]))
		i++;
	coor.y = ft_atoi(&str[i]);
	while(ft_isdigit(str[i]))
		i++;
	while(!ft_isdigit(str[i]))
		i++;
	coor.x = ft_atoi(&str[i]);
	return (coor);
}