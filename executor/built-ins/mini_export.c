/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:49:09 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/16 14:57:52 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

static char	*find_maximum(t_envp *envp_list)
{
	char	*maximum;
	int		index;

	index = -1;
	maximum = envp_list->variable;
	while (envp_list)
	{
		if (envp_compare(envp_list->variable, "_") && envp_list->type > 0)
			if (envp_compare(envp_list->variable, maximum) >= 0)
				maximum = envp_list->variable;
		envp_list = envp_list->next;
	}
	return (maximum);
}


static char	*find_minimum(t_envp *envp_list, char *last_minimum, char *maximum)
{
	char	*minimum;

	minimum = maximum;
	while (envp_list)
	{
		if (envp_compare(envp_list->variable, "_") && envp_list->type > 0)
			if (envp_compare(envp_list->variable, minimum) <= 0)
			{
				if (!last_minimum)
					minimum = envp_list->variable;
				else
					if (envp_compare(envp_list->variable, last_minimum) > 0)
						minimum = envp_list->variable;
			}
		envp_list = envp_list->next;
	}
	return (minimum);
}

static void	sort_and_print_envp(t_envp *envp)
{
	char	*minimum;
	char	*maximum;

	maximum = find_maximum(envp);
	minimum = NULL;
	while (minimum != maximum)
	{
		minimum = find_minimum(envp, minimum, maximum);
		print_line(minimum);
	}
}

static int	handle_argument(char *argument, t_envp **envp)
{
	char	*variable;
	int		type;

	type = 1;
	if (!(variable = ft_strdup(argument)))
		return (12);
	if (!(ft_strchr(variable, '=')))
		type = 2;
	if (envp_find_variable(*envp, variable) && type == 2)
		envp_change_type(*envp, variable, 1);
	else
		if (envp_replace_variable(envp, variable, type))
		{
			free (variable);
			return (12);
		}
	return (0);
}

int			mini_export(char **args,  t_envp **envp)
{
	int		index;
	int		sindex;

	errno = 0;
	if (!args[1])
		sort_and_print_envp(*envp);
	else
	{
		index = 0;
		while (args[++index])
		{
			if (!ft_isalpha(args[index][0]))
				return (error_arg_export(args[index]));
			sindex = 0;
			while (args[index][++sindex] != '=' && args[index][sindex])
				if (!ft_isalnum(args[index][sindex]) && \
					args[index][sindex] != '_' && args[index][sindex] != '=')
					return (error_arg_export(args[index]));
		}
		index = 0;
		while (args[++index])
			if (handle_argument(args[index], envp))
				return (12);
	}
	return (0);
}
