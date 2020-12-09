/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_management_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:41:17 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/09 16:05:02 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		try_close(int fd_1, int fd_2, int fd_3)
{
	int ret;

	ret = 0;
	if (fd_1 > 0 && close(fd_1) == -1)
		ret = error_print_return(NULL);
	if (fd_2 > 0 && close(fd_2) == -1)
		ret = error_print_return(NULL);
	if (fd_3 > 0 && close(fd_3) == -1)
		ret = error_print_return(NULL);
	return (ret);
}

int		error_fd(char *path, int fd_1, int fd_2, int fd_3)
{
	char	*error;
	int		tmp_err;

	write(1, "minishell: ", 11);
	if (path)
	{
		write(1, path, ft_strlen(path));
		write(1, ": ", 2);
	}
	error = strerror(errno);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	tmp_err = errno;
	try_close(fd_1, fd_2, fd_3);
	if (!errno)
		return (tmp_err);
	else
		return (errno);
}

int		comm_return_int(int return_value, char **memory)
{
	if (memory)
		free(memory);
	return (return_value);
}
