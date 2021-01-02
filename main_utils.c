/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:44:00 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 14:46:30 by sgertrud         ###   ########.fr       */
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

void	one_command(char **args, t_ijaor s)
{
	char *end;

	end = args[*(s.i)];
	args[*(s.i)] = 0;
	remove_terminal_mode();
	g_line()->sig = 9;
	if (args && args[*(s.j)] && (*s.and_or == -1 || (!*s.and_or && !*s.ret) ||
	(*s.and_or && *s.ret)))
		*s.ret = do_command(&args[*(s.j)], get_envp());
	if (!ft_strcmp(end, "&&"))
		*s.and_or = 0;
	if (!ft_strcmp(end, "||"))
		*s.and_or = 1;
	set_terminal_mode(envp_get_var_value(*get_envp(), "TERM"));
	if (end_command_str(end) && end)
		(*(s.i))++;
	free(end);
}

int		replace(char ***args, int *i)
{
	int len;

	while ((*args)[*i] && !end_command_str((*args)[*i]))
	{
		(*args)[*i] = replace_env((*args)[*i], *get_envp());
		(*args) = remake_args((*args), *i, &len);
		(*i) += len;
	}
	return (0);
}

int		full_command(char **str)
{
	char	**args;
	int		ret;
	int		and_or;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = -1;
	and_or = -1;
	args = parse_string(str);
	if (syntax_error_str(check_syntax(args)))
		return (free_matrix(args));
	while (args[i] && ft_strcmp(args[i], "\n") && ret != 130)
	{
		replace(&args, &i);
		one_command(args, (t_ijaor){&i, &j, &and_or, &ret});
		free_commands(args, j);
		j = i;
	}
	free_commands(args, i);
	free(args);
	return (0);
}
