/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:17:35 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/30 09:59:53 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	temp[4];
	int				i;

	if ((unsigned int)c > 127)
	{
		i = 0;
		while (c > 0)
		{
			temp[3 - i] = c % 64;
			temp[3 - i] += (c / 64 > 0 || temp[3 - i] > 16) * 128;
			c /= 64;
			i++;
		}
		if (temp[3 - i] > 16)
			i++;
		temp[3 - i] %= 16;
		temp[3 - i] += 128 + (i > 0) * 64 + (i > 1) * 32 + (i > 2) * 16;
		write(fd, &temp[3 - i], i + 1);
	}
	else
		write(fd, &c, 1);
}
