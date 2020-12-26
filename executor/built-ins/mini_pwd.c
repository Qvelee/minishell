/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:22:43 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/26 13:08:50 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include <errno.h>
#include <string.h>

int		mini_pwd(void)
{
	char	*buffer;
	char	*error;

	buffer = NULL;
	errno = 0;
	if (!(buffer = (getcwd(buffer, PATH_MAX))))
	{
		write(2, "minishell: pwd: ", 16);
		error = strerror(errno);
		write(2, error, ft_strlen(error));
		return (errno);
	}
	else
		write(1, buffer, ft_strlen(buffer));
	write(1, "\n", 1);
	free(buffer);
	return (0);
}
