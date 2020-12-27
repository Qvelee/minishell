/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:31:43 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/27 05:56:54 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		check_val(char c, char dcommand[2])
{
	return (((c == '|' || c == ';') && dcommand[0] != 92 &&
	(dcommand[1] || dcommand[0] == 0 || dcommand[0] == ';' || dcommand[0] == '<'
	|| dcommand[0] == '>')) || (c == ';' && (dcommand[0] == '|' || dcommand[1]))
	|| ((c == '|' || c == '&' || c == '>' || c == '<' || c == '&') &&
	dcommand[1] && dcommand[0] != 92) ||
	(c == '<' && dcommand[0] == '>') ||
	(c == '\n' && (dcommand[0] == '<' || dcommand[0] == '>')));
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

	dcommand = (char[2]){0, 0};
	quote = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
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
