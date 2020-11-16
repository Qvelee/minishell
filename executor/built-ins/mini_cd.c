/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:42:28 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/16 15:02:03 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static int	error_cd(int mode, char *set)
{
	char	*error;

	if (mode == 1)
	{
		write(2, "cd: ", 4);
		write(2, set, ft_strlen(set));
		write(2, ": ", 2);
		error = strerror(errno);
		write(2, error, ft_strlen(error));
		free(error);
		write(2, "\n", 1);
	}
	if (mode == 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (mode == 3)
	{
		write(2, "cd: ", 4);
		write(2, set, ft_strlen(set));
		write(2, " not set\n", 9);
		return (1);
	}
	return (errno);
}

static char	*get_oldpwd(t_envp *envp)
{
	char	*old_pwd;

	if (!(old_pwd = envp_get_var_value(envp, "PWD")))
	{
		if (!(old_pwd = envp_create_envp_str("OLDPWD", "")))
			return (NULL);
	}
	else
		if (!(old_pwd = envp_create_envp_str("OLDPWD", old_pwd)))
			return (NULL);
	return (old_pwd);
}

static char	*get_pwd(void)
{
	char	*error;
	char	*pwd;

	pwd = NULL;
	if (!(pwd = getcwd(pwd, PATH_MAX)))
	{
		error = strerror(errno);
		write(2, error, ft_strlen(error));
		return (NULL);
	}
	if (!(pwd = envp_create_envp_str("PWD", pwd)))
		return (NULL);
	return (pwd);
}

static int	cd_to_directory(t_envp **envp, char *directory)
{
	char	*old_pwd;
	char	*pwd;

	errno = 0;
	if ((chdir(directory) != -1))
	{
		if (!(old_pwd = get_oldpwd(*envp)))
			return (12);
		if (envp_replace_variable(envp, old_pwd, 0))
		{
			free(old_pwd);
			return (12);
		}
		if (!(pwd = get_pwd()))
			return (12);
		if (envp_replace_variable(envp, pwd, 0))
		{
			free(pwd);
			return (12);
		}
	}
	else
		return (error_cd(1, directory));
	return (0);
}

int			mini_cd(char **args, t_envp **envp)
{
	char	*directory;

	errno = 0;
	if (args[1] && args[2])
		return (error_cd(2, NULL));
	directory = args[1];
	if (!args[1])
		if (!(directory = envp_get_var_value(*envp, "HOME")))
			return (error_cd(3, "HOME"));
	if (args[1] && !ft_strncmp(args[1], "-", 2))
		if (!(directory = envp_get_var_value(*envp, "OLDPWD")))
			return (error_cd(3, "OLDPWD"));
	return (cd_to_directory(envp, directory));
}
