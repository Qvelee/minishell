/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:39:08 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/18 15:01:19 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int		mini_env(t_envp *envp)
{
	errno = 0;
	while (envp)
	{
		if (envp->type != 0 && envp->type != 2)
		{
			write(1, envp->variable, ft_strlen(envp->variable));
			write(1, "\n", 1);
		}
		envp = envp->next;
	}
	return (0);
}
