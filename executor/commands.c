/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:54:17 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/19 15:19:35 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		check_directory(char *command, char *directory)
{
	struct dirent	*dir;
	DIR				*dirp;

	if (!(dirp = opendir(directory)))
		return (0);
	while ((dir = readdir(dirp)))
		if (!ft_strcmp(command, dir->d_name))
			return (1);
	closedir(dirp);
	return (0);
}

char	*find_executable(char *command, char *path)
{
	char	**pathes;
	char	*executable;
	char	*temp;
	int		index;

	executable = NULL;
	index = -1;
	pathes = ft_split(path, ":");
	while (pathes[++index])
		if (check_directory(command, pathes[index]))
			break ;
	if (pathes[index])
	{
		temp = ft_strjoin(pathes[index], "/");
		executable = ft_strjoin(temp, command);
		free(temp);
	}
	free_matrix(pathes);
	return (executable);
}

int		command(char **args, t_envp **envp_list)
{
	char	**envp;
	char	*command;
	pid_t	pid;
	pid_t	wpid;
	int		return_value;

	return_value = -2;
	
	if (!(command = find_executable(args[0], envp_get_var_value(*envp_list, "PATH"))))
	{
		printf("minishell: |%s| command not found\n", args[0]);
		return (return_value);
	}
	envp = envp_lst_to_matrix(*envp_list);
	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, envp) == -1)
			perror(args[0]);
		exit(1);
	}
	else if (pid > 0)
	{
		wpid = waitpid(pid, &return_value, WNOHANG);
		while (!WIFEXITED(return_value) && !WIFSIGNALED(return_value))
			wpid = waitpid(pid, &return_value, WNOHANG);
	}
	else if (pid < 0)
		perror("minishell");
	free(envp);
	return (return_value);
}
