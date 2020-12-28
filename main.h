/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:07:08 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/28 14:28:30 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# ifndef BONUS
#  define BONUS 0
# endif
# define YELLOW	"\x1b[33m"
# define GREEN	"\x1b[32m"
# define RESET	"\x1b[0m"
# include "structs.h"

int						save_ret_value(int value, t_envp **envp_list);
int						do_command(char **args, t_envp **envp_list);
char					**parse_command(char **str, t_envp *envp);
char					check_validity(char *str);
t_envp					*envp_create_list(char **envp);
void					envp_lst_clear(t_envp **envp, void (*delete)(void*));
int						remove_terminal_mode(void);
void					free_matrix(char **memory);
void					exit_minishell(int code, char **args, t_envp **envp);
int						get_next_line(int fd, char **line);
void					ft_sigint(int __attribute__((unused)) sig);
void					ft_nothing(int __attribute__((unused)) sig);
void					add_histfile(t_envp *envp);
void					invite(char *str);
int						syntax_error(char c);
void					one_command(char **str, t_envp **envp);
int						check_sc(char c);
#endif
