/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:18:35 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 14:23:42 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "stdlib.h"
#include "libft.h"
#include "get_static.h"

void	invite(char *str)
{
	write(1, GREEN, 5);
	write(1, str, ft_strlen(str));
	write(1, RESET, 5);
}

int		syntax_error_str(char *c)
{
	if (c)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		if (!ft_strcmp(c, "\n"))
			write(2, "\\n", 2);
		else
			write(2, c, ft_strlen(c));
		write(2, "'\n", 2);
		save_ret_value(1, get_envp());
		return (1);
	}
	return (0);
}

void	free_commands(char **command, int i)
{
	while (command[i])
	{
		free(command[i]);
		command[i] = 0;
		i++;
	}
}

int		end_command_str(char *str)
{
	return (!(ft_strcmp(str, "&") && ft_strcmp(str, "&&")
	&& ft_strcmp(str, "||") && ft_strcmp(str, "(") && ft_strcmp(str, ")")
	&& ft_strcmp(str, ";") && ft_strcmp(str, "\n")));
}
