/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:31:43 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/22 15:25:16 by sgertrud         ###   ########.fr       */
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
	char quote;
	char dcommand[2] = {0,0};
	//flags = (t_flags){{'"',1},{'\'',1},{'<',1},{'>',1},{'&',1},{'|',1},{';',1},{'"',1},1};
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
		{
			//if (!dcommand[1])
				if (((*str == '|' || *str == ';') && (dcommand[1] || dcommand[0] == 0 || dcommand[0] == ';' || dcommand[0] == '<' || dcommand[0] == '>')) || ((*str == '\n') && (dcommand[0] == '|' || dcommand[0] == '>' || dcommand[0] == '<' || dcommand[1])) || (*str == ';' && (dcommand[0] == '|' || dcommand[1])) || ((*str == '|' || *str == '&' || *str == '>' || *str == '<' || *str == '&') && dcommand[1]) || (*str == '<' && dcommand[0] == '>') || (*str == '\n' && (dcommand[0] == '<' || dcommand[0] == '>')))
					return (*str);
		}
		if ((*str == '>' && *(str + 1) == '>') || (*str == '<' && *(str + 1) == '<') || (*str == '|' && *(str + 1) == '|') || (*str == '&' && *(str + 1) == '&'))
		{
			dcommand[0] = *str;
			dcommand[1] = *(str + 1);
			str += 2;
		}
		else
		{
			dcommand[0] = *str;
			dcommand[1] = 0;
			str +=1;
		}
	}
	return (0);
}