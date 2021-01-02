/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_treatment_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:27:23 by nelisabe          #+#    #+#             */
/*   Updated: 2021/01/02 15:57:20 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
**	envp_compare works like strcmp, but considers '=' symbol as
**	the end of the line.
*/

int		envp_compare(char *var_in_envp, char *var_to_check)
{
	int		index;

	index = 0;
	while (var_in_envp[index] && var_to_check[index])
	{
		if (var_in_envp[index] != var_to_check[index])
			break ;
		if (var_in_envp[index] == '=' || var_to_check[index] == '=')
			break ;
		index++;
	}
	if ((var_in_envp[index] == '=' && var_to_check[index] == '\0') || \
		(var_in_envp[index] == '\0' && var_to_check[index] == '='))
		return (0);
	return (var_in_envp[index] - var_to_check[index]);
}

/*
**	envp_get_var_value returns pointer to place in memory, where
**	begins the value of specified variable. if no variable was
**	found, NULL is returned.
*/

char	*envp_get_var_value(t_envp *envp_list, char *variable)
{
	if (!variable)
		return (NULL);
	while (envp_list)
	{
		if (!envp_compare(envp_list->variable, variable))
		{
			if (envp_list->type == 2)
				return (NULL);
			return (ft_strchr(envp_list->variable, '=') + 1);
		}
		envp_list = envp_list->next;
	}
	return (NULL);
}

/*
**	envp_find_variable returns link to element of list with specified
**	variable, if no element was found, NULL is returned.
*/

t_envp	*envp_find_variable(t_envp *envp_list, char *variable)
{
	while (envp_list)
	{
		if (!envp_compare(envp_list->variable, variable))
			return (envp_list);
		envp_list = envp_list->next;
	}
	return (NULL);
}

/*
**	envp_replace_variable check if variable is already in list.
**	if yes:
**		if variable type is not 1, it will be changed to specified.
**		old variable will be freed and link will be changed to new varibale.
**	if no:
**		new element of list will be created with specified variable and type.
**		function will add it to the end of the list.
**	if memory error happaned, value != 0 is returned.
*/

int		envp_replace_variable(t_envp **envp_list, char *variable, int type)
{
	t_envp	*envp_element;
	t_envp	*link;

	if ((link = envp_find_variable(*envp_list, variable)))
	{
		if (link->type != 1)
			link->type = type;
		free(link->variable);
		link->variable = variable;
	}
	else
	{
		if (!(envp_element = envp_lst_new(variable, type)))
			return (12);
		envp_add_to_lst_back(envp_element, envp_list);
	}
	return (0);
}

/*
**	envp_lst_to_matrix creates NULL terminated array of pointers
**	to strings, pointed by envp_list->variable, except type != 1
**	elements.
**	usege of this array after colling any list-changing functions
**	is dangerous, because function just copies list's pointers and
**	not allocate new memery for them.
**	if memmory error happaned, NULL is returned.
*/

char	**envp_lst_to_matrix(t_envp *envp_list)
{
	char	**envp;
	int		index;

	index = envp_lst_type_size(envp_list, 1);
	if (!(envp = (char**)malloc(sizeof(char*) * (index + 1))))
		return (NULL);
	index = -1;
	while (envp_list)
	{
		if (envp_list->type == 1)
			envp[++index] = envp_list->variable;
		envp_list = envp_list->next;
	}
	envp[++index] = NULL;
	return (envp);
}
