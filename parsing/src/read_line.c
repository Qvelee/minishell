/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:53:12 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:21:02 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse_internal.h"
#include "get_static.h"
#include "fcntl.h"
#include "unistd.h"
#include "libft.h"
#include "executor_external.h"

char	*read_line(t_envp *envp)
{
	int			fd;
	int			ret;
	t_history	*history;
	int			i;
	char		*histfile;

	ret = 1;
	i = 0;
	fd = -1;
	if ((histfile = envp_get_var_value(envp, "HISTFILE")))
		fd = open(histfile, O_CREAT | O_RDWR | O_APPEND, 0666);
	history = 0;
	if (fd > 0)
		history = read_history(fd);
	*get_line() = (t_line){ft_calloc(1, BUFF_SIZE), &i, 10, BUFF_SIZE};
	get_line()->str[0] = 0;
	*(get_cursor()) = get_cursor_start();
	history = add_history(history, ft_strdup(get_line()->str));
	handle_one_sym(ret, history, &i, envp);
	if (get_line()->str && *get_line()->str != 4)
		move_to_out(get_line()->str, fd, i);
	if (fd > 0)
		close(fd);
	free_history(history);
	return (get_line()->str);
}
