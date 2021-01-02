/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 05:28:22 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 02:41:19 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_internal.h"
#include "libft.h"
#include "get_static.h"

char	**ft_djoin(char **args, char **buff)
{
	int		len;
	int		i;
	char	**newargs;

	i = 0;
	len = 0;
	while (args && args[i++])
		len++;
	i = 0;
	while (buff && buff[i++])
		len++;
	newargs = malloc((len + 1) * sizeof(char*));
	i = -1;
	len = -1;
	while (args && args[++i])
		newargs[++len] = args[i];
	i = -1;
	while (buff && buff[++i])
		newargs[++len] = buff[i];
	newargs[len + 1] = 0;
	free(args);
	return (newargs);
}

char	**parse_string(char **str)
{
	char	**full;
	char	**buff;

	full = 0;
	while (*(*str))
	{
		if (((**str == '&' && *(*str + 1) == '&') ||
		(**str == '|' && *(*str + 1) == '|')) && (*str += 2))
			full = ft_djoin(full, (char*[2]){ft_substr(*str - 2, 0, 2), 0});
		else if (**str == '|' || **str == '&' || **str == ';' || **str == '\n')
			full = ft_djoin(full, (char*[2]){ft_substr((*str)++, 0, 1), 0});
		else
		{
			buff = parse_command(str, *get_envp(), 1);
			full = ft_djoin(full, buff);
			free(buff);
		}
	}
	return (full);
}

char	*replace_env(char *arg, t_envp *envp)
{
	char *add;
	char *newarg;
	char *temp;

	temp = arg;
	newarg = 0;
	while (!check_end_arg(*arg))
		if (*arg == '$' && !check_end_arg(*(arg + 1)) &&
		(ft_isalpha(*(arg + 1)) || (*(arg + 1)) == '_' ||
		(*(arg + 1)) == '?') && (add = parse_env(&arg, envp)))
			newarg = join_free(newarg, add);
		else
			newarg = join_free(newarg, (char[2]){(*arg++), 0});
	free(temp);
	return (newarg);
}
/*
char	**ft_djoin(char **args, char **buff)
{
	int		len;
	int		i;
	char	**newargs;

	i = 0;
	len = 0;
	while (args && args[i++])
		len++;
	i = 0;
	while (buff && buff[i++])
		len++;
	newargs = malloc((len + 1) * sizeof(char*));
	i = -1;
	len = -1;
	while (args && args[++i])
		newargs[++len] = args[i];
	i = -1;
	while (buff && buff[++i])
		newargs[++len] = buff[i];
	newargs[len + 1] = 0;
	free(args);
	return (newargs);
}

char	***command_by_end(char **str)
{
	char	***full;
	char	**buff;

	full = 0;
	while (*(*str) && *(*str) != '\n')
	{
		if (((**str == '&' && *(*str + 1) == '&') ||
		(**str == '|' && *(*str + 1) == '|')) && (*str += 2))
			full = ft_djoin(full, (char*[2]){ft_substr(*str - 2, 0, 2), 0});
		else if (**str == '|' || **str == '&' || **str == ';')
			full = ft_djoin(full, (char*[2]){ft_substr((*str)++ , 0, 1), 0});
		else
		{
			buff = parse_command(str, *get_envp(), 1);
			full = ft_djoin(full, buff);
			free(buff);
		}
	}
	return (full);
}*/