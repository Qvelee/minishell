/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_treatment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:39:27 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/09 13:16:56 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	error_read_line(char *memory, int *fd)
{
	errno = 12;
	error_print_return(NULL);
	free(memory);
	try_close(*fd, -1, -1);
	return (12);
}

static int	handle_input(char *line, char *stop_word, int *fd)
{
	int		index;

	index = -1;
	if (!line)
		return (12);
	while (line[++index])
		if (line[index] == '\n')
			line[index] = '\0';
	if (!ft_strcmp(line, stop_word))
		return (1);
	write(1, "> ", 2);
	write(*fd, line, ft_strlen(line));
	write(*fd, "\n", 1);
	free(line);
	return (0);
}

static int	get_input(char *stop_word, int *fd, t_envp *envp)
{
	char	*line;
	char	*path;
	int		ret;
	
	set_terminal_mode(envp_get_var_value(envp, "TERM"));
	if (!(path = ft_strjoin("/tmp/", stop_word)))
		return (error_print_return(NULL));
	if ((*fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (error_return_int(error_fd(path, -1, -1, -1), path, \
															NULL, NULL));
	write(1, "> ", 2);
	while ((line = read_line(envp)))
		if ((ret = handle_input(line, stop_word, fd)) == 12)
			return (error_read_line(path, fd));
		else if (ret == 1)
			break ;
	if ((ret = try_close(*fd, -1, -1)))
		return (error_return_int(ret, path, NULL, NULL));
	if ((*fd = open(path, O_RDONLY, 0444)) == -1)
		return (error_return_int(error_fd(path, -1, -1, -1), path, \
															NULL, NULL));
	free(line);
	free(path);
	remove_terminal_mode();
	return (0);
}

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
