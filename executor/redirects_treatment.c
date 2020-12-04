/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_treatment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:39:27 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/04 15:56:49 by nelisabe         ###   ########.fr       */
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

int		get_input(char *word)
{
	char	*line;
	char	*path;
	int		fd;
	
	path = ft_strjoin("/tmp/", word);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (get_next_input(&line))
	{
		if (!ft_strcmp(line, word))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(path, O_RDONLY, 0444);
	free(line);
	return (fd);
}

int		redirect_input(char *path, int *fd_in, int mode)
{
	if (!path)
		return (error_syntax('\n'));
	else
	{
		if (*fd_in != -1)
			close(*fd_in);
		if (mode == 1)
			*fd_in = open(path, O_RDONLY, 0644);
		else
			*fd_in = get_input(path);
	}
	return (0);
}

int		redirect_output(char *path, int *fd_out, int mode)
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
			*fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	return (0);
}
