/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 20:10:57 by nelisabe          #+#    #+#             */
/*   Updated: 2020/12/27 19:38:02 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <termios.h>



int		save_ret_value(int value, t_envp **envp_list)
{
	char	*value_to_save;
	char	*temp;

	if (!(temp = ft_itoa(value)))
		return (error_print_return(NULL));
	if (!(value_to_save = envp_create_envp_str("?", temp)))
	{
		free(temp);
		return (error_print_return(NULL));
	}
	free(temp);
	if (envp_replace_variable(envp_list, value_to_save, 0))
	{
		free(value_to_save);
		return (error_print_return(NULL));
	}
	return (0);
}

int		wait_pid(int pid_temp)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = (pid_t)pid_temp;
	if ((waitpid(pid, &status, WUNTRACED) == -1))
		error_print_return(NULL);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		if ((waitpid(pid, &status, WUNTRACED) == -1))
			error_print_return(NULL);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			ret = 130;
		if (WTERMSIG(status) == 3)
			ret = 131;
	}
	else
		ret = WEXITSTATUS(status);
	return (ret);
}

int		brackets(char ***args, int *flag)
{
	int			ret;

	*flag = 0;
	ret = brackets_treatment(args, flag);
	if (ret < 0)
	{
		ret = wait_pid(ret * -1);
		return(ret);
	}
	printf("%d %d\n", ret, *flag);
	return (-1);
}

int		do_command(char **args, t_envp **envp_list)
{
	int			return_value;
	int			flag;
	t_commands	*commands;

	if ((return_value = brackets(&args, &flag)) != -1)
		return (return_value);
	if (!(return_value = parse_command_ex(args, &commands, *envp_list)))
	{
		if ((return_value = run_commands(commands, envp_list, flag)))
		{
			comm_lst_clr(&commands);
			if (check_fatal_error(return_value))
				exit_fatal(return_value, args, envp_list);
		}
	}
	else
	{
		if (check_fatal_error(return_value))
			exit_fatal(return_value, args, envp_list);
	}
	comm_lst_clr(&commands);
	if (save_ret_value(return_value, envp_list))
		exit_fatal(12, args, envp_list);
	return (return_value);
}
