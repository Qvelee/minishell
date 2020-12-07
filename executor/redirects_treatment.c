/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_treatment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:39:27 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/07 18:24:14 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		get_next_input(char **line)
{
	char	buff[1];
	char	*tmp;
	int		ret;

	if (!line)
		return (-1);
	*line = ft_strdup("");
	while ((ret = read(0, buff, 1)))
	{
		if (ret == -1)
		{
			free(*line);
			return (-1);
		}
		else if (buff[0] != '\n')
		{
			tmp = *line;
			*line = ft_strjoin(*line, buff);
			free(tmp);
		}
		else
			return (1);
	}
	return (ret);
}

int		get_input(char *word, int *fd)
{
	char	*line;
	char	*path;
	int		ret;
	
	if (!(path = ft_strjoin("/tmp/", word)))
		return (error_print_return(NULL) * -1);
	if ((*fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0444)) == -1)	
		return (error_return_int(error_fd(path, -1, -1, -1), path, \
															NULL, NULL));
	while (get_next_input(&line))
	{
		if (!ft_strcmp(line, word))
			break ;
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
	}
	if ((ret = try_close(*fd, -1, -1)))
		return (error_return_int(ret * -1, path, NULL, NULL));
	if ((*fd = open(path, O_RDONLY, 0444)) == -1)
		return (error_return_int(error_fd(path, -1, -1, -1), path, \
															NULL, NULL));
	free(line);
	free(path);
	return (0);
}

int		redirect_input(char *path, int *fd_in, int mode)
{
	int		ret;

	if (!path)
		return (error_syntax('\n'));
	else
	{
		if (*fd_in > 0)
			if ((ret = try_close(*fd_in, -1, -1)))
				return (ret * -1);
		if (mode == 1)
		{
			if ((*fd_in = open(path, O_RDONLY, 0644)) == -1)
				return (error_fd(path, -1, -1, -1));
		}
		else
			if ((ret = get_input(path, fd_in)))
				return (ret);
	}
	return (0);
}

int		redirect_output(char *path, int *fd_out, int mode)
{
	int		ret;

	if (!path)
		return (error_syntax('\n'));
	else
	{
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
	}
	return (0);
}
