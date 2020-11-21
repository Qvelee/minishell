/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:32:15 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/21 17:19:11 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	error_too_many_args()
{
	write(2, "minishell: exit: too many arguments\n", 36);
	return (1);
}

static int	error_numeric_argument(char *wrong_argument, char **args, \
	t_envp **envp_list, t_term term)
{
	write(2, "minishell: exit: ", 17);
	write(2, wrong_argument, ft_strlen(wrong_argument));
	write(2, ": numeric argument required\n", 28);
	remove_terminal_mode(term);
	envp_lst_clear(envp_list, free);
	free_matrix(args);
	return (2);
}

static int	norm_exit(int code, char **args, t_envp **envp_list, t_term term)
{
	remove_terminal_mode(term);
	envp_lst_clear(envp_list, free);
	free_matrix(args);
	write(1, "exit\n", 5);
	return (code);
}

int			mini_exit(char **args, t_envp **envp_list, t_term term)
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
				exit(norm_exit(ret, args, envp_list, term));
			}
			else
				exit(error_numeric_argument(args[1], args, envp_list, term));
		}
		else
			return (error_too_many_args());
	}
	exit(norm_exit(0, args, envp_list, term));
}
