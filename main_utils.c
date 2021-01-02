/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:44:00 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 04:50:55 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "executor.h"
#include "parse_internal.h"
#include "get_static.h"
#include "parse_internal.h"

void	add_histfile(t_envp *envp)
{
	char	*hf;
	int		len;
	char	*temp;
	char	*home;

	home = envp_get_var_value(envp, "HOME");
	temp = envp_get_var_value(envp, "_");
	hf = 0;
	if (home)
		hf = ft_strjoin(home, "/.minishell_history");
	else if (temp)
	{
		len = ft_strlen(temp) - 9;
		if (!ft_strncmp(&temp[len], "minishell", 9))
			hf = join_free(ft_substr(temp, 0, len), ".minishell_history");
	}
	if (hf)
		envp_add_to_lst_back(envp_lst_new(envp_create_envp_str("HISTFILE",
		hf), 0), &envp);
	free(hf);
}

void	invite(char *str)
{
	write(1, GREEN, 5);
	write(1, str, ft_strlen(str));
	write(1, RESET, 5);
}

int		syntax_error(char c)
{
	if (c)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		if (c == '\n')
			write(2, "\\n", 2);
		else
			write(2, &c, 1);
		write(2, "'\n", 2);
		save_ret_value(1, get_envp());
	}
	return (c);
}

int		syntax_error_str(char *c)
{
	if (c)
	{
		write(2, "minishell: syntax error near unexpected token '", 47);
		if (!ft_strcmp(c, "\n"))
			write(2, "\\n", 2);
		else
			write(2, c, ft_strlen(c));
		write(2, "'\n", 2);
		save_ret_value(1, get_envp());
		return (1);
	}
	return (0);
}

void	free_commands(char **command)
{
	int		i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free(command);
}

int		end_command_str(char *str)
{
	return (!(ft_strcmp(str, "&") && ft_strcmp(str, "&&") && ft_strcmp(str, "||")
	&& ft_strcmp(str, "(") && ft_strcmp(str, ")") && ft_strcmp(str, ";")
	&& ft_strcmp(str, "\n")));
}

void	one_command(char **str, t_envp **envp)
{
	char	**args;
	int		ret;
	int		and_or;
	int		i;
	int		j;
	char	*end;

	i = 0;
	j = 0;
	ret = -1;
	and_or = -1;
	args = parse_string(str);
	if (syntax_error_str(check_syntax(args)))
	{
		free_matrix(args);
		return ;
	}
	while (args[i] && ft_strcmp(args[i], "\n") && ret != 130)
	{
		/*command = make_command(args);
		i = remake_args(args, i);
		args[i] = replace_env(args[i], *envp);*/
		while (args[i] && !end_command_str(args[i]))
			i++;
		end = args[i];
		args[i] = 0;
		remove_terminal_mode();
		g_line()->sig = 9;
		if (args && args[j] && (and_or == -1 || (!and_or && !ret) ||
		(and_or && ret)))
			ret = do_command(&args[j], envp);
		if (!ft_strcmp(end, "&&"))
			and_or = 0;
		if (!ft_strcmp(end, "||"))
			and_or = 1;
		set_terminal_mode(envp_get_var_value(*envp, "TERM"));
		if (end_command_str(end) && end)
			(i)++;
		free(end);
		while ((args[j]))
			free((args[j++]));
		args[0] = 0;
		j = i;
	}
	j = 0;
	free_matrix(args);
}

/*char *make_command(char ***args)
{
	char **command;

	command = 0;
	while (!end_command_str(*(*args)))
	{
		command = ft_djoin(command, (*args));
		(*args)++;
	}
	return(command);
}*/