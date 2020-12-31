/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 05:36:57 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/29 20:25:11 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H
# include "structs.h"

char		**ft_djoin(char **args, char **buff);
char		*check_syntax(char **c);
char		*replace_env(char *arg, t_envp *envp);
char		**parse_string(char **str);
char		**parse_command(char **str, t_envp *envp, int full);
void		handle_back_slash(char **str, char **arg);
char		*parse_d_quote(char **str, t_envp *envp, int full);
char		*parse_quote(char **str);
char		*parse_env(char **str, t_envp *envp);
int			check_end_arg(char c);
int			check_end_command(char c);
int			check_and_or(char c, char h);
int			check_sc(char c);
int			check_wild(char *str);
#endif
