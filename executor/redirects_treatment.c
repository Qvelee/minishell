/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_treatment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:39:27 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/09 15:18:12 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int			redirect_input(char *path, int *fd_in, int mode, t_envp *envp)
{
	int		ret;

	if (*fd_in > 0)
		if ((ret = try_close(*fd_in, -1, -1)))
			return (ret * -1);
	if (mode == 1)
	{
		if ((*fd_in = open(path, O_RDONLY, 0644)) == -1)
			return (error_fd(path, -1, -1, -1));
	}
	else
		if ((ret = get_input(path, fd_in, envp)))
			return (ret);
	return (0);
}

int			redirect_output(char *path, int *fd_out, int mode)
{
	int		ret;

	if (*fd_out > 0)
		if ((ret = try_close(*fd_out, -1, -1)))
			return (ret * -1);
	if (mode == 1)
	{
		if ((*fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644)) \
															== -1)
			return (error_fd(path, -1, -1, -1));
	}
	else
		if ((*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644)) \
															== -1)
			return (error_fd(path, -1, -1, -1));
	return (0);
}
