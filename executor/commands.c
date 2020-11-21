/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:17 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/21 16:16:03 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exec_error(char **args)
{
	if (errno == 2)
	{
		if (args[0][0] == '/' || args[0][0] == '.')
			return (error_print_return(args[0]));
		else
			return (127);
	}
	return (error_print_return(args[0]));
}

static int	run_exec(char *command, char **args, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(command, args, envp);
		exit(exec_error(args));
	}
	else if (pid > 0)
	{
		if ((wpid = waitpid(pid, &status, WUNTRACED)) == -1)
			return (error_print_return(args[0]));
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			if ((wpid = waitpid(pid, &status, WUNTRACED)) == -1)
				return (error_print_return(args[0]));
		return (WEXITSTATUS(status));
	}
	else
		return (error_print_return(args[0]));
}

static int	check_directory(char *command, char *directory)
{
	struct dirent	*dir;
	DIR				*dirp;
	int				ret;

	errno = 0;
	ret = 1;
	if (!(dirp = opendir(directory)))
		return (ret);
	while ((dir = readdir(dirp)))
		if (!ft_strcmp(command, dir->d_name))
			ret = 0;
	if (closedir(dirp) == -1)
		return (error_print_return(directory));
	return (ret);
}

static int	find_executable_in_path(char **final_command, char *command, \
	char *path)
{
	char	**pathes;
	char	*temp;
	int		index;

	if (!path)
		return (2);
	*final_command = NULL;
	index = -1;
	if (!(pathes = ft_split(path, ":")))
		return (12);
	while (pathes[++index])
		if (!check_directory(command, pathes[index]))
			break ;
	if (pathes[index])
	{
		if (!(temp = ft_strjoin(pathes[index], "/")))
			return (error_return_int(12, NULL, NULL, pathes));
		if (!(*final_command = ft_strjoin(temp, command)))
			return (error_return_int(12, temp, NULL, pathes));
		free(temp);
	}
	free_matrix(pathes);
	if (!(*final_command))
		return (2);
	return (0);
}

int			command(char **args, t_envp **envp_list)
{
	char	**envp;
	char	*command;
	int		return_value;

	errno = 0;
	return_value = find_executable_in_path(&command, args[0], \
		envp_get_var_value(*envp_list, "PATH"));
	if (return_value == 12)
		return (12);
	else if (return_value == 2)
		if (!(command = ft_strdup(args[0])))
			return (12);
	if (!(envp = envp_lst_to_matrix(*envp_list)))
		return (error_return_int(12, command, NULL, NULL));
	return_value = run_exec(command, args, envp);
	free(command);
	free(envp);
	return (return_value);
}
