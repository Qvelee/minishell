/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:31:43 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/29 11:15:12 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_internal.h"
#include "libft.h"

int		check_val(char c, char dc[2])
{
	return (((c == '|' || c == ';') && dc[0] != 92 &&
	(dc[1] || dc[0] == 0 || dc[0] == ';' || dc[0] == '<' || dc[0] == '>'))
	|| (c == ';' && (dc[0] == '|' || dc[1]))
	|| ((c == '|' || c == '&') && dc[1] && dc[0] != 92)
	|| (c == '<' && dc[0] == '>')
	|| (c == '\n' && (dc[0] == '<' || dc[0] == '>'))
	|| ((c == '&' || c == '|') && dc[0] == '(')
	|| (c == ')' && (dc[0] == '&' || dc[0] == '|'))
	|| (c == '(' && !(check_end_command(dc[0]) || dc[0] == '|' || dc[0] == '('))
	|| (dc[0] == ')' && !(check_end_command(c) || c == '|' || c == ')')));
}

int		check_red(char c, char b)
{
	return ((c == '>' && b == '>') || (c == '<' &&
		b == '<') || (c == '|' && b == '|') ||
		(c == '&' && b == '&'));
}

char	check_validity(char *str)
{
	char quote;
	char *dcommand;
	char par;

	par = 0;
	dcommand = (char[2]){0, 0};
	quote = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '(' && !quote)
			par++;
		if (*str == ')' && !quote)
			par--;
		if (par < 0)
			return (')');
		if ((*str == '"' || *str == '\'') && !quote)
			quote = *str++;
		if (*str == '\\' && !quote)
			dcommand = (char[2]){'\\', *((str += 2) - 1)};
		if ((*str == '"' || *str == '\'') && quote == *str)
			quote = 0;
		if (!quote && check_val(*str, dcommand))
			return (*str);
		dcommand[0] = *str;
		if (!check_red(*str, *(str + 1)) && str++)
			dcommand[1] = 0;
		else
			dcommand[1] = *((str += 2) - 1);
	}
	return (0);
}
