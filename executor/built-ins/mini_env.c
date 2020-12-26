/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:39:08 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/26 13:11:43 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include <errno.h>
#include <string.h>

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
