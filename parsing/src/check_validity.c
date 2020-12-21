/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:31:43 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/21 03:48:22 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_flag
{
	char ch;
	int val;
}		t_flag;
typedef struct s_flags
{
	t_flag quote;
	t_flag d_quote;
	t_flag r_left;
	t_flag r_right;
	t_flag and;
	t_flag or;
	t_flag semicolon;
	t_flag brackets;
}				t_flags;

char check_validity(char *str)
{
	t_flags flags;
	char prev;
	char quote;

	//flags = (t_flags){{'"',1},{'\'',1},{'<',1},{'>',1},{'&',1},{'|',1},{';',1},{'"',1},1};
	prev = 0;
	quote = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if ((*str == '"' || *str == '\'') && !quote)
			quote = *str++;
		if ((*str == '"' || *str == '\'') && quote == *str)
			quote = 0;
		if (!quote)
			if (((*str == '|' || *str == ';') && (prev == 0 || prev == ';' || prev == '<' )) || ((*str == '\n') && (prev == '|' || prev == '>' || prev == '<')) || (*str == ';' && prev == '|'))
				return (*str);
		prev = *str;
		str++;
	}
	return (0);
}