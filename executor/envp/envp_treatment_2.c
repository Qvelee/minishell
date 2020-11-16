/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_treatment_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:46:49 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/15 12:34:19 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

char	*envp_create_envp_str(char *variable, char *value)
{
	char	*envp_str;

	if (!(variable = ft_strjoin(variable, "=")))
		return (NULL);
	if (!(envp_str = ft_strjoin(variable, value)))
		return (NULL);
	free(variable);
	return (envp_str);
}

void	envp_change_type(t_envp *envp_list, char *variable, int type)
{
	t_envp	*link;

	if ((link = envp_find_variable(envp_list, variable)))
		link->type = type;
}

void	envp_remove_from_list(t_envp **envp_list, char *variable)
{
	t_envp	*delete;
	t_envp	*previous;
	t_envp	*temp;

	if (!(delete = envp_find_variable(*envp_list, variable)))
		return ;
	temp = *envp_list;
	previous = *envp_list;
	while (temp)
	{
		if (temp == delete)
			break ;
		previous = temp;
		temp = temp->next;
	}
	if (delete == previous)
		*envp_list = (*envp_list)->next;
	else
		previous->next = delete->next;
	envp_delete_element(delete, free);
}

/*
**	envp_create_list creates list from matrix and returns delete
**	to the first list's element. if error occures, no memory leaks
**	are possible and return will be NULL.
*/

t_envp	*envp_create_list(char **_envp)
{
	t_envp	*envp_list;
	t_envp	*envp_element;
	char	*memory;
	int		index;

	index = -1;
	envp_list = NULL;
	while (_envp[++index])
	{
		if (!(memory = ft_strdup(_envp[index])))
		{
			envp_lst_clear(&envp_list, free);
			return (NULL);
		}
		if (!(envp_element = envp_lst_new(memory, 1)))
		{
			free(memory);
			envp_lst_clear(&envp_list, free);
			return (NULL);
		}
		envp_add_to_lst_back(envp_element, &envp_list);
	}
	return (envp_list);
}
