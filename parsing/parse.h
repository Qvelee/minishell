/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:05:06 by sgertrud          #+#    #+#             */
/*   Updated: 2020/11/17 20:09:47 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# define BUFF_SIZE 1024
# include <termios.h>
# include <stddef.h>
# include "main.h"

int		set_terminal_mode(struct termios term);
int		remove_terminal_mode(struct termios term);
char	*read_line(struct termios term, t_envp *envp);
int		check_end(char c);
int		handle_escape_sequance(char *command, t_envp *envp);
char	**parse_command(char **str, t_envp *envp);
char	*parse_d_quote(char **str, t_envp *envp);
char	*parse_quote(char **str);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*get_envp_value(char *var, t_envp *envp);
char	**ft_realloc(char **data, size_t len, size_t newlen);
char	*parse_env(char **str, t_envp *envp);
#endif