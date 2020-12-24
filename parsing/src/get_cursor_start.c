/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 20:28:59 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/24 10:50:43 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "termcap.h"
#include "sys/ioctl.h"
t_coor get_cursor_start(void)
{
	t_coor coor;
	char str[20];
	int i;
	int n;
	int ret;
	i = 0;
	coor = (t_coor){MSH + 1, 1};
	tputs(tgetstr("u7", 0), 1, ft_putchar);
	ret = read(0, str, 20);
	while (ioctl(0, FIONREAD, &n) == 0 && n > 0)
		ret += read(0, &str[ret], 20);

	while (i < ret && !ft_isdigit(str[i]))
		i++;
	if (i < ret)
		coor.y = ft_atoi(&str[i]);
	while (i < ret && ft_isdigit(str[i]))
		i++;
	while (i < ret && !ft_isdigit(str[i]))
		i++;
	if (i < ret)
		coor.x = ft_atoi(&str[i]);
	return (coor);
}