/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 09:33:04 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/30 09:24:29 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H
# include "structs.h"
# ifndef BONUS
#  define BONUS 0
# endif

int			get_next_line(int fd, char **line);
void		realloc_str(int ret);
char		*read_one_sym(int *ret);
void		handle_one_sym(int ret, t_history *history, size_t *i);
int			set_curpos_home(char *start, char *end);
int			set_curpos_end(char *start, char *end);
void		move_rest(char *str, size_t i, int ret);
void		handle_chars(char *str, char *sym, size_t *i, int ret);
void		move_to_out(char *str, int fd, size_t i);
void		cursor_dec(char *start, char *end);
void		cursor_inc(t_coor *cursor, int len);
void		cursor_dec(char *start, char *end);
int			handle_keys(char *c, char **str, size_t *i, t_history **h);
t_history	*read_history(int fd);
t_history	*add_history(t_history *head, char *str);
void		free_history(t_history *history);
void		go_right(char *str, size_t *i);
void		go_left(char *str, size_t *i);
void		check_arrows(char *c, char **st, size_t *i, t_history **his);
void		check_ctrl(char *c, char **str, size_t *i, size_t len_c);
void		history_down(t_history **history, char **str, size_t *i);
void		history_up(t_history **history, char **str, size_t *i);
#endif
