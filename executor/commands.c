/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:17 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/21 13:46:34 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		run_exec(char *command, char **args, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(command, args, envp);
		return (error_print_return(args[0]));
	}
	else if (pid > 0)
	{
		if ((wpid = waitpid(pid, &status, WUNTRACED)) == -1)
			return (error_print_return("minishell"));
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			if ((wpid = waitpid(pid, &status, WUNTRACED)) == -1)
				return (error_print_return("minishell"));
		return (WEXITSTATUS(status));
	}
	else
		return (error_print_return("minishell"));
}

int		check_directory(char *command, char *directory)
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

char	*find_executable(char *command, char *path)
{
	char	**pathes;
	char	*executable;
	char	*temp;
	int		index;

	executable = NULL;
	index = -1;
	if (!(pathes = ft_split(path, ":")))
		return (NULL);
	while (pathes[++index])
		if (!check_directory(command, pathes[index]))
			break ;
	if (pathes[index])
	{
		if (!(temp = ft_strjoin(pathes[index], "/")))
			return (error_return_char(NULL, NULL, pathes));
		if (!(executable = ft_strjoin(temp, command)))
			return (error_return_char(temp, NULL, pathes));
		free(temp);
	}
	free_matrix(pathes);
	return (executable);
}

int		command(char **args, t_envp **envp_list)
{
	char	**envp;
	char	*command;
	int		return_value;

	errno = 0;
	if (!(command = find_executable(args[0], \
		envp_get_var_value(*envp_list, "PATH"))))
		return (127);
	if (!(envp = envp_lst_to_matrix(*envp_list)))
		return (error_return_int(12, command, NULL, NULL));
	return_value = run_exec(command, args, envp);
	free(command);
	free(envp);
	return (return_value);
}
