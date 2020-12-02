/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:32:46 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/02 20:01:43 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <linux/limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include "main.h"
# include "libft.h"

typedef struct	s_commands
{
	char				**command;
	int					fd_in;
	int					fd_out;
	struct s_commands	*next;
}				t_commands;

typedef struct	s_exec
{
	int		return_value;
	int		fd_pipe[2];
	int		fd_out;
	int		fd_in;
	int		tmp_in;
	int		tmp_out;
	int		count;
	int		index;
	int		*pids;
	int		status;
}				t_exec;


void	check_memory_error(int code, char **args, t_envp **envp_list, t_term term);
int		parse_command_ex(char **args, t_commands **commands);
int		built_in(char **args, t_envp **envp_list, t_term term);
int		mini_echo(char **args);
int		mini_pwd(void);
int		mini_cd(char **args, t_envp **envp);
int		mini_export(char **args, t_envp **envp_list);
int		error_arg_export(char *argument);
void	print_line(char *line);
int		mini_unset(char **args, t_envp **envp);
int		mini_env(t_envp *envp);
int		mini_exit(char **args, t_envp **envp_list, t_term term);
int		command(char **args, t_envp **envp_list);
char	*error_return_char(char *memory_1, char *memory_2, char **matrix);
int		error_return_int(int return_value, char *memory_1, char *memory_2, \
	char **matrix);
int		error_print_return(char *massage);
int		error_command_not_found(char *command);
int		error_syntax(char symbol);

int			save_ret_value(int value, t_envp **envp_list);
int			run_commands(t_commands *commands, t_envp **envp_list, t_term term);
int			redirect_output(char *path, int *fd_out, int *fd_in, int mode);

/*
**	envp treatment prototypes
*/

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

t_commands	*comm_lst_new(char **args, int fd_in, int fd_out);
t_commands	*comm_last_element(t_commands *commands);
void		comm_add_back(t_commands *command, t_commands **commands);
void		comm_lst_clr(t_commands **commands);
int			comm_lst_size(t_commands *commands);
int			comm_error_return_int(int return_value, char **memory);

#endif
