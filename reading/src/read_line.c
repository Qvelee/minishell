/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:53:12 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 05:21:34 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "get_static.h"
#include "fcntl.h"
#include "unistd.h"
#include "libft.h"
#include "executor_external.h"
#include "ft_readline.h"

void	handle_one_sym(int ret, t_history *history, size_t *i)
{
	char *sym;

	sym = read_one_sym(&ret);
	while (sym[0] != 10 && sym[0] != 13 && !(sym[ret] = 0))
	{
		if ((!g_line()->str[0] && sym[0] == 4) || sym[0] == 3)
		{
			g_line()->str[0] = sym[0];
			g_line()->str[1] = 0;
			free(sym);
			break ;
		}
		if (sym[0] != 4 && (g_line()->sig = 10))
		{
			realloc_str(ret);
			if (((sym[0] > 0 && sym[0] <= 31) || sym[0] == 127) && sym[0] != 4)
				handle_keys(sym, &g_line()->str, i, &history);
			else
				handle_chars(g_line()->str, sym, i, ret);
			free(sym);
		}
		sym = read_one_sym(&ret);
	}
	free(sym);
}

void	bonus_read(t_envp *envp, size_t *i)
{
	char		*histfile;
	int			fd;
	t_history	*history;
	int			ret;

	fd = -1;
	ret = 1;
	*i = 0;
	if ((histfile = envp_get_var_value(envp, "HISTFILE")))
		fd = open(histfile, O_CREAT | O_RDWR | O_APPEND, 0666);
	history = 0;
	if (fd > 0)
		history = read_history(fd);
	history = add_history(history, ft_strdup(g_line()->str));
	*(get_cursor()) = get_cursor_start();
	handle_one_sym(ret, history, i);
	if (g_line()->str && *g_line()->str != 4 && *g_line()->str != 3)
		move_to_out(g_line()->str, fd, *i);
	if (fd > 0)
		close(fd);
	free_history(history);
}

char	*read_line(t_envp *envp)
{
	size_t	i;

	*g_line() = (t_line){ft_calloc(1, BUFF_SIZE), &i, 10, BUFF_SIZE};
	g_line()->str[0] = 0;
	if (BONUS)
		bonus_read(envp, &i);
	else
		read(0, g_line()->str, BUFF_SIZE);
	return (g_line()->str);
}
