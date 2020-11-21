/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:32:15 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/21 13:37:48 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	error_too_many_args()
{
	write(2, "exit: ", 6);
	write(2, "too many arguments\n", 19);
	return (1);
}

static int	error_numeric_argument(char *wrong_argument, char **args)
{
	write(2, "exit: ", 6);
	write(2, wrong_argument, ft_strlen(wrong_argument));
	write(2, ": ", 2);
	write(2, "numeric argument required\n", 26);
	free_matrix(args);
	return (2);
}

static int	norm_exit(int code, char **args)
{
	free_matrix(args);
	write(1, "exit\n", 5);
	return (code);
}

int			mini_exit(char **args)
{
	int	index;
	int ret;

	index = -1;
	errno = 0;
	if (args[1])
	{
		if (!args[2])
		{
			while (args[1][++index])
				if (!ft_isdigit(args[1][index]))
					break ;
			if (args[1][index] == '\0')
			{
				ret = ft_atoi(args[1]);
				exit(norm_exit(ret, args));
			}
			else
				exit(error_numeric_argument(args[1], args));
		}
		else
			return (error_too_many_args());
	}
	exit(norm_exit(0, args));
}
