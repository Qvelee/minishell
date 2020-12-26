/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:05:06 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:30:52 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_EXTERNAL_H
# define EXECUTOR_EXTERNAL_H

# include <termios.h>
# include <stddef.h>
# include "main.h"
# include "parse_internal.h"

# include "structs.h"

int			do_command(char **args, t_envp **envp_list);
char		*envp_get_var_value(t_envp *envp, char *variable);

/*
** int			set_terminal_mode(char *term_name);
** int			remove_terminal_mode(void);
** char		*read_line(t_envp *envp);
** t_coor		get_cursor_start(void);
** void		cursor_inc(t_coor *cursor, int len);
** char		*ft_realloc_str(char *data, size_t len, size_t newlen);
*/

#endif
