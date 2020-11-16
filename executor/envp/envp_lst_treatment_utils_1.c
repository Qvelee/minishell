/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst_treatment_utils_1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:27:23 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/13 20:05:31 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
**	envp_lst_type_size returns count of elements with given type.
**	if parameter type is -1, function will count all elements.
*/

int		envp_lst_type_size(t_envp *envp_list, int type)
{
	int		count;

	count = 0;
	while (envp_list)
	{
		if (envp_list->type == type || type == -1)
			count++;
		envp_list = envp_list->next;
	}
	return (count);
}

/*
**	envp_last_element returns pointer to the last element of envp_list
*/

t_envp	*envp_last_element(t_envp *envp_list)
{
	while (envp_list)
	{
		if (!(envp_list->next))
			break ;
		envp_list = envp_list->next;
	}
	return (envp_list);
}

/*
**	envp_add_to_lst_back adds given envp_element to the end of the list
*/

void	envp_add_to_lst_back(t_envp *envp_element, t_envp **envp_list)
{
	t_envp	*temp;

	if (!(*envp_list))
		*envp_list = envp_element;
	else
	{
		temp = envp_last_element(*envp_list);
		temp->next = envp_element;
	}
}

/*
**	envp_lst_new creates new t_envp element and set it's variable and type
*/

t_envp	*envp_lst_new(char *variable, int type)
{
	t_envp	*new_element;

	if (!(new_element = (t_envp*)malloc(sizeof(t_envp))))
		return (NULL);
	new_element->type = type;
	new_element->variable = variable;
	new_element->next = NULL;
	return (new_element);
}
