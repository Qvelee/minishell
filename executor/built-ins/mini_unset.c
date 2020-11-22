/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:43:31 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/22 14:38:14 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	error_arg(char *argument)
{
	write(2, "minishell: unset: `", 19);
	write(2, argument, ft_strlen(argument));
	write(2, "\': Not a valid identifier\n", 26);
	return (1);
}

int			mini_unset(char **args, t_envp **envp)
{
	int		index;
	int		sindex;

	errno = 0;
	if (!args[1])
		return (0);
	index = 0;
	while (args[++index])
	{
		if (!ft_isalpha(args[index][0]))
			return (error_arg(args[index]));
		sindex = 0;
		while (args[index][++sindex])
			if (!ft_isalnum(args[index][sindex]) && \
				args[index][sindex] != '_')
				return (error_arg(args[index]));
	}
	index = 0;
	while (args[++index])
		envp_remove_from_list(envp, args[index]);
	return (0);
}
