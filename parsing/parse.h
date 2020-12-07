/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:05:06 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/07 18:32:43 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define BUFF_SIZE 1024
# include <termios.h>
# include <stddef.h>
# include "main.h"

typedef struct	s_coor
{
	int x;
	int y;
}				t_coor;

typedef struct	s_line
{
	char *str;
	int i;
}				t_line;

int		set_terminal_mode(char *term_name);
int		remove_terminal_mode(void);
char	*read_line(t_envp *envp);
int		check_end(char c);
int		handle_escape_sequence(char *command, t_envp *envp, char *str, int *i);
char	**parse_command(char **str, t_envp *envp);
char	*parse_d_quote(char **str, t_envp *envp);
char	*parse_quote(char **str);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*get_envp_value(char *var, t_envp *envp);
char	**ft_realloc(char **data, size_t len, size_t newlen);
char	*parse_env(char **str, t_envp *envp);
int		ft_putchar(int c);
t_line	*get_line(void);
t_coor	get_term_size(void);
t_coor	get_cursor(void);

#endif