/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checked.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:15:05 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 02:40:26 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ora(char *c)
{
	return (!(ft_strcmp(c, "&") && ft_strcmp(c, "&&") &&
		ft_strcmp(c, "|") && ft_strcmp(c, "||")));
}

int		red(char *c)
{
	return (!(ft_strcmp(c, ">") && ft_strcmp(c, ">>") &&
		ft_strcmp(c, "<") && ft_strcmp(c, "<<")));
}

char	*check_syntax(char **c)
{
	int		par;
	char	*p;

	par = 0;
	p = 0;
	while (*c)
	{
		if (!ft_strcmp(*c, ")"))
			par--;
		if (!ft_strcmp(*c, "("))
			par++;
		if ((par < 0)
			|| (!ft_strcmp(*c, ";") && (p == 0 || !ft_strcmp(p, ";") || red(p)
			|| ora(p)))
			|| (!ft_strcmp(*c, "\n") && red(p))
			|| (ora(*c) && (ora(p) || red(p) || !ft_strcmp(p, "(")
			|| p == 0 || !ft_strcmp(p, ";")))
			|| (!ft_strcmp(*c, "(") && (!(ora(p) && ft_strcmp(p, "(")
			&& ft_strcmp(p, ";")) && ft_strcmp(p, ";") && p != 0))
			|| (!ft_strcmp(*c, ")") && (red(p) || ora(p) || !ft_strcmp(p, "(")))
			|| (red(*c) && red(p))
			|| (!ft_strcmp(p, ")") && !ora(*c) && !red(*c)))
			return (*c);
		p = *c;
		c++;
	}
	return (0);
}
