/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:05:06 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/25 04:58:05 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define BUFF_SIZE 1024
# include <termios.h>
# include <stddef.h>
# include "main.h"
# define MSH 11
typedef struct	s_coor
{
	int x;
	int y;
}				t_coor;

typedef struct	t_history
{
	char *str;
	struct t_history *next;
	struct t_history *prev;
}				t_history;
typedef struct	s_line
{
	char **str;
	int *i;
	char sig;
	int size;
}				t_line;

int			set_terminal_mode(char *term_name);
int			remove_terminal_mode(void);
char		*read_line(t_envp *envp);
int			check_end_arg(char c);
int			check_end_command(char c);
int			check_and_or(char c, char h);
int			handle_escape_sequence(char *command, t_envp *envp, char **str, int *i, t_history **history);
char		**parse_command(char **str, t_envp *envp);
char		*parse_d_quote(char **str, t_envp *envp);
char		*parse_quote(char **str);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
char		*get_envp_value(char *var, t_envp *envp);
char		**ft_realloc(char **data, size_t len, size_t newlen);
char		*parse_env(char **str, t_envp *envp);
int			ft_putchar(int c);
t_line		*get_line(void);
t_coor		get_term_size(void);
t_coor		*get_cursor(void);
t_history	*read_history(int fd);
t_history	*add_history(t_history *head, char *str);
t_coor			*savecursor();
void		free_history(t_history *history);
void		set_curpos_home(char *start, char *end);
void		set_curpos_end(char *start, char *end);
char		check_validity(char *str);
t_envp		**get_envp(void);
t_coor		get_cursor_start(void);
void		cursor_inc(t_coor *cursor, int len);
char		*ft_realloc_str(char *data, size_t len, size_t newlen);
void					cursor_dec(char *start, char *end);
int			check_wild(char *str);
#endif