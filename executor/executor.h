/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:32:46 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/28 17:56:59 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <linux/limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft.h"
# include "structs.h"

typedef struct	s_commands
{
	char				**command;
	int					fd_in;
	int					fd_out;
	char				*fd_in_end;
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

/*
**	built-ins
*/

int				built_in(char **args, t_envp **envp_list, int mode);
int				mini_echo(char **args);
int				mini_pwd(void);
int				mini_cd(char **args, t_envp **envp);
int				mini_export(char **args, t_envp **envp_list);
int				error_arg_export(char *argument);
void			print_line(char *line);
int				mini_unset(char **args, t_envp **envp);
int				mini_env(t_envp *envp);
int				mini_exit(char **args, t_envp **envp_list, int mode);

/*
**	command treatment (parsing)
*/

int				parse_command_ex(char **args, t_commands **commands, \
	t_envp *envp);
int				redirect_output(char *path, int *fd_out, int mode);
int				redirect_input(char *path, int *fd_in, int mode, t_envp *envp);
int				get_input(char *stop_word, int *fd, t_envp *envp);
char			*read_line(t_envp *envp);
int				set_terminal_mode(char *term_name);
int				set_terminal_mode2(void);
int				remove_terminal_mode(void);

/*
**	executor
*/

int				init_exec(t_exec *exec, t_commands *commands);
int				check_sc(char c);
int				run_commands(t_commands *commands, t_envp **envp_list, \
	int exec_mode);
int				end_of_commands(t_exec *exec);
int				error_running(int return_value, t_commands *command, \
	t_exec *exec);
int				error_fd(char *path, int fd_1, int fd_2);
int				try_close(int *fd_1, int *fd_2);
int				command(char **args, t_envp **envp_list, int exec_mode);
int				save_ret_value(int value, t_envp **envp_list);
void			remove_slashes(t_commands *commands);
void			free_matrix(char **memory);
void			exit_minishell(int code, char **args, t_envp **envp);

/*
**	errors treament
*/

int				check_fatal_error(int code);
int				error_return_int(int return_value, char *memory_1, \
	char *memory_2, char **matrix);
int				error_print_return(char *massage);
int				error_command_not_found(char *command);
void			exit_fatal(int code, char **args, t_envp **envp_list);
int				error_return_print(int ret, char *message);

/*
**	envp treatment prototypes
*/

t_envp			*envp_lst_new(char *variable, int type);
void			envp_add_to_lst_back(t_envp *envp_element, t_envp **envp_list);
t_envp			*envp_last_element(t_envp *envp_list);
int				envp_lst_type_size(t_envp *envp_list, int type);
void			envp_delete_element(t_envp *envp_element, \
	void (*delete)(void *));
int				envp_compare(char *var_in_envp, char *var_to_check);
void			envp_remove_from_list(t_envp **envp_list, char *variable);
char			*envp_create_envp_str(char *variable, char *value);
void			envp_change_type(t_envp *envp_list, char *variable, int type);
char			*envp_get_var_value(t_envp *envp_list, char *variable);
t_envp			*envp_find_variable(t_envp *envp_list, char *variable);
int				envp_replace_variable(t_envp **envp_list, char *variable, \
	int type);
char			**envp_lst_to_matrix(t_envp *envp_list);
void			envp_lst_clear(t_envp **envp_list, void (*delete)(void*));

/*
**	command treatment prototypes
*/

t_commands		*comm_lst_new(char **args, int fd_in, int fd_out);
t_commands		*comm_last_element(t_commands *commands);
void			comm_add_back(t_commands *command, t_commands **commands);
void			comm_lst_clr(t_commands **commands);
int				comm_lst_size(t_commands *commands);
int				comm_return_int(int return_value, char **memory);

#endif
