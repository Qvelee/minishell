/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 05:36:57 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/27 05:54:18 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H
# include "structs.h"

void		handle_back_slash(char **str, char **arg);
char		*parse_d_quote(char **str, t_envp *envp);
char		*parse_quote(char **str);
char		*parse_env(char **str, t_envp *envp);
int			check_end_arg(char c);
int			check_end_command(char c);
int			check_and_or(char c, char h);
int			check_sc(char c);
int			set_curpos_home(char *start, char *end);
int			set_curpos_end(char *start, char *end);
void		move_rest(char *str, int i, int ret);
void		handle_chars(char *str, char *sym, int *i, int ret);
void		move_to_out(char *str, int fd, int i);
char		*read_one_sym(int *ret);
void		handle_one_sym(int ret, t_history *history, int *i, t_envp *envp);
void		cursor_dec(char *start, char *end);
void		cursor_inc(t_coor *cursor, int len);
int			handle_escape_sequence(char *c, char **str, int *i, t_history **h);
t_history	*read_history(int fd);
t_history	*add_history(t_history *head, char *str);
void		free_history(t_history *history);
void		go_right(char *str, int *i);
void		go_left(char *str, int *i);
void		check_arrows(char *c, char **st, int *i, t_history **his);
void		check_ctrl(char *c, char **str, int *i, int len_c);
void		history_down(t_history **history, char **str, int *i);
void		history_up(t_history **history, char **str, int *i);
void		cursor_dec(char *start, char *end);
int			check_wild(char *str);
#endif
