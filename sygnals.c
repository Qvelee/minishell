/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sygnals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:44:22 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/15 10:37:18 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_static.h"
#include "structs.h"
#include "libft.h"
#include "main.h"

void	ft_sigint_bonus(int __attribute__((unused)) sig)
{
	int		j;
	char	*str;
	int		len;

	str = (g_line()->str);
	len = ft_strlen(str);
	write(1, "\n", 1);
	j = (ft_substrlen(str, &str[*(g_line()->i)]) + MSH) / get_term_size().x;
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

void	ft_sigint(int __attribute__((unused)) sig)
{
	if (g_line()->sig == 10)
	{
		if (BONUS)
			ft_sigint_bonus(sig);
		else
		{
			write(1, "\n", 1);
			invite("minishell: ");
		}
	}
	save_ret_value(130, get_envp());
}

void	ft_nothing(int __attribute__((unused)) sig)
{
}
