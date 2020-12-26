/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:46:57 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:20:06 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "glob.h"
#include "parse_internal.h"

void	parse_one_step(char **str, char **arg, t_envp *envp)
{
	char	*add;

	if (**str == '\\')
	{
		(*arg) = ft_strjoin_gnl((*arg), (char[2]){*(*str + 1), 0});
		*str += 2;
	}
	else if (**str == '\"' && (*str)++)
	{
		add = parse_d_quote(str, envp);
		(*arg) = ft_strjoin_gnl((*arg), add);
		free(add);
	}
	else if (**str == 39 && (*str)++)
	{
		add = parse_quote(str);
		(*arg) = ft_strjoin_gnl((*arg), add);
		free(add);
	}
	else if (**str == '$' && !check_end_arg((*(*str + 1))) &&
	(ft_isalpha(*(*str + 1)) || (*(*str + 1)) == '_' ||
	(*(*str + 1)) == '?') && (add = parse_env(str, envp)))
		(*arg) = ft_strjoin_gnl((*arg), add);
	else
		(*arg) = ft_strjoin_gnl((*arg), (char[2]){(*(*str)++), 0});
}

char	*parse_arg(char **str, t_envp *envp)
{
	char	*arg;

	arg = 0;
	if (**str == '|')
		return (ft_substr((*str)++, 0, 1));
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
			return (ft_substr((*str += 2) - 2, 0, 2));
		else
			return (ft_substr((*str)++, 0, 1));
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
			return (ft_substr((*str += 2) - 2, 0, 2));
		else
			return (ft_substr((*str)++, 0, 1));
	}
	while (**str != '\n' && **str != ' ' && !check_end_arg(**str))
	{
		parse_one_step(str, &arg, envp);
	}
	return (arg);
}

int		remake_args(char **args, int i)
{
	glob_t	buff;
	int		j;

	j = 0;
	glob(args[i], GLOB_NOCHECK, NULL, &buff);
	free(args[i]);
	while (buff.gl_pathv[j])
	{
		args[i] = ft_strdup(buff.gl_pathv[j]);
		j++;
		i++;
	}
	globfree(&buff);
	return (i);
}

char	**parse_command(char **str, t_envp *envp)
{
	int		i;
	char	**args;
	int		size;

	args = (char**)malloc((int)BUFF_SIZE * sizeof(char*));
	i = 0;
	size = BUFF_SIZE;
	while (**str == ' ')
		(*str)++;
	while (**str != '\n' && **str != 0 && !check_end_command(**str) &&
	!(check_and_or(**str, *(*str + 1))))
	{
		if (i > size && (args = ft_realloc(args, size, size * 2)))
			size *= 2;
		args[i] = parse_arg(str, envp);
		if (check_wild(args[i]))
			i = remake_args(args, i);
		else
			i++;
		while (**str == ' ')
			(*str)++;
	}
	args[i] = 0;
	return (args);
}
