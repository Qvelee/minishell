/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:46:57 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/22 16:19:12 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "main.h"


char *parse_d_quote(char **str, t_envp *envp)
{
	int i;
	char *var;
	char *add;
	char *arg;

	arg = 0;
	add = 0;
	while (**str != '\"' && **str)
	{
		if (**str == '\\' && ((*((*str) + 1) == '$' || (*((*str) + 1) == '"')) ||  (*((*str) + 1) == '\\')))
		{
			(*str)++;
			add = ft_substr(*str,0,1);
			(*str)++;
			arg = ft_strjoin_gnl(arg,add);
			free(add);
		}
		else if (**str == '$')
		{
			add = parse_env(str, envp);
			arg = ft_strjoin_gnl(arg,add);
		}
		else
		{
			add = ft_substr(*str,0,1);
			(*str)++;
			arg = ft_strjoin_gnl(arg,add);
			free(add);
		}
	}
	(*str)++;
	return (arg);
}

char *parse_quote(char **str)
{
	int i;
	char *add;

	i = 0;
	while ((*str)[i] != 39 && (*str)[i])
		i++;
	add = ft_substr(*str,0,i);
	*str += i + 1;
	return (add);
}

char *parse_env(char **str, t_envp *envp)
{
	int i;
	char *var;
	char *add;
	char *arg;

	add = 0;
	i = 1;
	while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
		i++;
	if ((*str)[0] == '$' && (*str)[1] == '?')
		i++;
	var = ft_substr(*str,1,i - 1);
	*str += i;
	if (*var != 0)
		add = envp_get_var_value(envp,var);
	free(var);
	return (add);
}

char *parse_arg(char** str,t_envp *envp)
{
	char *var;
	char *value;
	char *arg;
	char *add;
	int i;

	arg = ft_calloc(BUFF_SIZE, 1);
	add = 0;
	if (**str == '|')
		return (ft_substr((*str)++,0,1));
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
			return(ft_substr((*str += 2) - 2,0,2));
		else
			return(ft_substr((*str)++,0,1));
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
			return(ft_substr((*str += 2) - 2,0,2));
		else
			return(ft_substr((*str)++,0,1));
	}

	while (**str != '\n' && **str != ' ' && !check_end_arg(**str))
	{
		if (**str == '\\')
		{
			(*str)++;
			add = ft_substr(*str,0,1);
			(*str)++;
			arg = ft_strjoin_gnl(arg,add);
			free(add);
			add = 0;
		}
		else if (**str == '\"')
		{
			(*str)++;
			add = parse_d_quote(str,envp);
			arg = ft_strjoin_gnl(arg,add);
			free(add);
			add = 0;
		}
		else if (**str == 39)
		{
			(*str)++;
			add = parse_quote(str);
			arg = ft_strjoin_gnl(arg,add);
			free(add);
			add = 0;
		}
		else if (**str == '$' && !check_end_arg((*(*str + 1))))
			{
				add = parse_env(str, envp);
				arg = ft_strjoin_gnl(arg,add);
			}
		else
		{
			add = ft_substr(*str,0,1);
			(*str)++;
			arg = ft_strjoin_gnl(arg,add);
			free(add);
			add = 0;
		}
	}
	return (arg);
}


char **parse_command(char** str,t_envp *envp)
{
	int i;
	int d_quotes;
	int quotes;

	char **args;
	char *arg;
	int size;

	args = malloc(BUFF_SIZE * sizeof(char*));

	quotes = 0;
	i = 0;
	d_quotes = 0;
	size = BUFF_SIZE;
	while (**str == ' ')
			(*str)++;
	while (**str != '\n' && **str != 0 && !check_end_command(**str))
	{
		if (i > size)
		{
			args = ft_realloc(args,size,size * 2);
			size *= 2;
		}
		args[i] = parse_arg(str,envp);
		i++;
		while (**str == ' ')
			(*str)++;
	}
	args[i] = 0;
	return (args);
}