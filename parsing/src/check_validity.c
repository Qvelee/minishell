/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:31:43 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 04:51:14 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_internal.h"
#include "libft.h"

int		check_val(char c, char d[2])
{
	return (((c == '|' || c == ';') && d[0] != 92 &&
	(d[1] || d[0] == 0 || d[0] == ';'))
	|| (c == ';' && (d[0] == '|' || d[0] == '&' || d[0] == ';' || d[0] == 0
	|| d[0] == '<' || d[0] == '>'))
	|| (c == '\n' && (d[0] == '<' || d[0] == '>'))
	|| ((c == '|' || c == '&') && (d[0] == '|' || d[0] == '&' || d[0] == '>'
	|| d[0] == '<' || d[0] == 0 || d[0] == '(' || d[0] == ';'))
	|| (c == '<' && d[0] == '>')
	|| ((c == '&' || c == '|') && d[0] == '(')
	|| (c == ')' && (d[0] == '&' || d[0] == '|'))
	|| (c == '(' && !(d[0] == '&' || d[0] == '|' || d[0] == '('))
	|| (d[0] == ')' && !(check_end_command(c) || c == '|' || c == ')')));
}

int		check_red(char c, char b)
{
	return ((c == '>' && b == '>') || (c == '<' &&
		b == '<') || (c == '|' && b == '|') ||
		(c == '&' && b == '&'));
}

void	check_validity_helper(char **str, int *par, char quote)
{
	while (*(*str) == ' ')
		(*str)++;
	if (*(*str) == '(' && !quote)
		(*par)++;
	if (*(*str) == ')' && !quote)
		(*par)--;
}

int		check_validity_helper_2(char **str, char *quote, char dc[2])
{
	if ((*(*str) == '"' || *(*str) == '\'') && !(*quote))
		(*quote) = *(*str)++;
	else if (*(*str) == '\\' && !(*quote) && *((*str) + 1) && (dc[0] = '\\'))
		dc[1] = *(((*str) += 2) - 1);
	else if ((*(*str) == '"' || *(*str) == '\'') && (*quote) == *(*str))
		(*quote) = 0;
	else if (!(*quote) && check_val(*(*str), dc))
		return (*(*str));
	return (0);
}

char	check_validity(char *str)
{
	char	quote;
	char	*dc;
	int		par;

	par = 0;
	dc = (char[2]){0, 0};
	quote = 0;
	while (*str)
	{
		check_validity_helper(&str, &par, quote);
		if (par < 0)
			return (')');
		if (check_validity_helper_2(&str, &quote, dc))
			return (*str);
		dc[0] = *str;
		if (!check_red(*str, *(str + 1)) && str++)
			dc[1] = 0;
		else
			dc[1] = *((str += 2) - 1);
	}
	return (0);
}
