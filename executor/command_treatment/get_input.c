/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:18:14 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/28 15:02:39 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <errno.h>
#include "get_static.h"

static int	error_read_line(char *memory, int *fd, int ret)
{
	errno = 12;
	if (ret != 130)
		error_print_return(NULL);
	free(memory);
	try_close(fd, NULL);
	return (ret);
}

static int	warning(int *count, char *stop_word)
{
	write(1, "minishell: warning: here-document at line ", 42);
	ft_putnbr_fd(*count, 1);
	write(1, " delimited by end-of-file (wanted `", 35);
	write(1, stop_word, ft_strlen(stop_word));
	write(1, "`)\n", 3);
	*count = 0;
	return (0);
}

static int	handle_input(char *line, char *stop_word, int *fd)
{
	int			index;

	index = -1;
	while (line[++index])
		if (line[index] == '\n')
			line[index] = '\0';
	if (!ft_strcmp(line, stop_word))
		return (1);
	write(1, "msheredoc> ", 11);
	write(*fd, line, ft_strlen(line));
	write(*fd, "\n", 1);
	return (0);
}

static int	read_input(int *fd, char *stop_word, t_envp *envp)
{
	static int	count;
	char		*line;
	char		tmp;

	write(1, "msheredoc> ", 11);
	while (*(line = read_line(envp)) != 3 && *line)
	{
		count++;
		if (line[0] == 4)
		{
			warning(&count, stop_word);
			break ;
		}
		if (handle_input(line, stop_word, fd))
			break ;
		free(line);
	}
	tmp = line[0];
	free(line);
	if (tmp == 3)
		return (error_return_print(130, "\n"));
	count = 0;
	if (errno == 12)
		return (12);
	return (0);
}

int			get_input(char *stop_word, int *fd, t_envp *envp)
{
	char	*path;
	int		ret;

	set_terminal_mode(envp_get_var_value(envp, "TERM"));
	set_terminal_mode2();
	if (!(path = ft_strjoin("/tmp/", stop_word)))
		return (error_print_return(NULL));
	if ((*fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (error_return_int(error_fd(NULL, -1, -1), path, NULL, NULL));
	if ((ret = read_input(fd, stop_word, envp)))
		return (error_read_line(path, fd, ret));
	if ((ret = try_close(fd, NULL)))
		return (error_return_int(ret, path, NULL, NULL));
	if ((*fd = open(path, O_RDONLY, 0444)) == -1)
		return (error_return_int(error_fd(NULL, -1, -1), path, NULL, NULL));
	free(path);
	remove_terminal_mode();
	return (0);
}
