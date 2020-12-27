/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:44:22 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 13:55:25 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_static.h"
#include "structs.h"
#include "libft.h"
#include "main.h"

void	ft_sigint(int __attribute__((unused)) sig)
{
	int		j;
	char	*str;
	int		i;
	int		len;

	if (g_line()->sig == 22)
		g_line()->sig = 20;
	if (g_line()->sig == 10)
	{
		i = *(g_line()->i);
		str = (g_line()->str);
		len = ft_strlen(str);
		write(1, "\n", 1);
		j = (ft_substrlen(str, &str[i]) + MSH) / get_term_size().x;
		len = (ft_substrlen(str, &str[len - 1]) + MSH) / get_term_size().x;
		while (j++ < len && len)
			write(1, "\n", 1);
		invite("minishell: ");
		if (g_line()->str && *(g_line()->str))
			*(g_line()->str) = 0;
		get_cursor()->x = MSH + 1;
		get_cursor()->y += 1;
		*(g_line()->i) = 0;
	}
	save_ret_value(130, get_envp());
}

void	ft_nothing(int __attribute__((unused)) sig)
{
}