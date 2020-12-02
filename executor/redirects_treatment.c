/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_treatment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:39:27 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/02 20:08:20 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int			redirect_output(char *path, int *fd_out, int *fd_in, int mode)
{
	if (!path)
		return (error_syntax('\n'));
	else
	{
		if (*fd_out != -1)
			close(*fd_out);
		if (mode == 1)
			*fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND);
	}
	return (0);
}
