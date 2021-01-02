/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 05:32:03 by sgertrud          #+#    #+#             */
/*   Updated: 2021/01/02 22:13:54 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "executor_external.h"
#include "parse_internal.h"

void	handle_back_slash(char **str, char **arg)
{
	(*arg) = join_free((*arg), (char[2]){*(*str + 1), 0});
	(*str) += 2;
}

char	*parse_env(char **str, t_envp *envp)
{
	size_t		i;
	char		*var;
	char		*add;

	add = 0;
	i = 1;
	while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
		i++;
	if ((*str)[0] == '$' && (*str)[1] == '?')
		i++;
	var = ft_substr(*str, 1, i - 1);
	*str += i;
	if (*var != 0)
		add = envp_get_var_value(envp, var);
	free(var);
	return (add);
}

char	*parse_d_quote(char **str, t_envp *envp, int full)
{
	char	*add;
	char	*arg;

	arg = 0;
	add = 0;
	while (**str != '\"' && **str)
		if (**str == '\\' && (*(*str + 1) == '$' || *(*str + 1) == '\\'))
			arg = join_free(arg, (char[3]){'\\', *((*str += 2) - 1), 0});
		else if (**str == '\\' && *(*str + 1) == '"')
			arg = join_free(arg, (char[2]){*((*str += 2) - 1), 0});
		else if (check_sc(**str) && **str != '$')
			arg = join_free(arg, (char[3]){'\\', *(*str)++, 0});
		else if (!full && **str == '$' && (ft_isalpha(*(*str + 1))
		|| *(*str + 1) == 95))
			arg = join_free(arg, parse_env(str, envp));
		else
		{
			add = ft_substr((*str)++, 0, 1);
			arg = join_free(arg, add);
			free(add);
		}
	(*str)++;
	return (arg);
}

char	*parse_quote(char **str)
{
	size_t		i;
	char		*arg;

	arg = ft_strdup("");
	i = 0;
	while ((*str)[i] != 39 && (*str)[i])
	{
		if (check_sc((*str)[i]))
			arg = join_free(arg, (char[3]){'\\', (*str)[i], 0});
		else
			arg = join_free(arg, (char[2]){(*str)[i], 0});
		i++;
	}
	*str += i + 1;
	return (arg);
}
