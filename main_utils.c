/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:44:00 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/27 09:44:31 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "executor.h"
#include "parse_internal.h"
#include "get_static.h"

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
			hf = ft_strjoin_gnl(ft_substr(temp, 0, len), ".minishell_history");
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
		write(1, "minishell: syntax error near unexpected token '", 47);
		if (c == '\n')
			write(1, "\\n", 2);
		else
			write(1, &c, 1);
		write(1, "'\n", 2);
		save_ret_value(1, get_envp());
	}
	return (c);
}

void	free_commands(char **command)
{
	int		i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free(command);
}

void	one_command(char **str, t_envp **envp)
{
	char	**command;
	int		ret;
	int		and_or;

	ret = -1;
	and_or = -1;
	while (*(*str) && *(*str) != '\n')
	{
		command = parse_command(str, *envp);
		remove_terminal_mode();
		g_line()->str = (*str);
		g_line()->sig = 9;
		if (command && *command && (and_or == -1 || (!and_or && !ret) ||
		(and_or && ret)))
			ret = do_command(command, envp);
		if (**str == '&' && *(*str + 1) == '&' && (*str += 2))
			and_or = 0;
		if (**str == '|' && *(*str + 1) == '|' && (*str += 2))
			and_or = 1;
		set_terminal_mode(envp_get_var_value(*envp, "TERM"));
		free_commands(command);
		if (*(*str) == ';')
			(*str)++;
	}
}
