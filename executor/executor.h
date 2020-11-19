/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:32:46 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/19 13:59:39 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <linux/limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "main.h"
# include "libft.h"

int		mini_echo(char **args);
int		mini_pwd(void);
int		mini_cd(char **args, t_envp **envp);
int		mini_export(char **args, t_envp **envp_list);
int		error_arg_export(char *argument);
void	print_line(char *line);
int		mini_unset(char **args, t_envp **envp);
int		mini_exit(char **args);
int		mini_env(t_envp *envp);
int		command(char **args, t_envp **envp_list);
t_envp	*envp_lst_new(char *variable, int type);
void	envp_add_to_lst_back(t_envp *envp_element, t_envp **envp_list);
t_envp	*envp_last_element(t_envp *envp_list);
int		envp_lst_type_size(t_envp *envp_list, int type);
void	envp_delete_element(t_envp *envp_element, void (*delete)(void *));
int		envp_compare(char *var_in_envp, char *var_to_check);
void	envp_remove_from_list(t_envp **envp_list, char *variable);
char	*envp_create_envp_str(char *variable, char *value);
void	envp_change_type(t_envp *envp_list, char *variable, int type);
char	*envp_get_var_value(t_envp *envp_list, char *variable);
t_envp	*envp_find_variable(t_envp *envp_list, char *variable);
int		envp_replace_variable(t_envp **envp_list, char *variable, int type);
char	**envp_lst_to_matrix(t_envp *envp_list);
void	envp_lst_clear(t_envp **envp_list, void (*delete)(void*));


#endif
