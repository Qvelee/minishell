/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:56:00 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/25 05:07:37 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_end_arg(char c)
{
	return (c == '\n' || c == ';' || c == '&' ||  c == '|' || c == '>' || c == '<' || c == ' ' || c == 0);
}
int	check_end_command(char c)
{
	return (c == '\n' || c == ';' || c == '&' || c == 0);
}
int check_spec_sym(char c)
{
	return (c == '$' || c == ';' || c == '&' || c == 0);
}

int check_and_or(char c, char h)
{
	return(c == h && (h == '|' || h == '&'));
}
int check_wild(char *str)
{
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}