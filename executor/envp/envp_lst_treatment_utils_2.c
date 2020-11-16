/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst_treatment_utils_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:27:23 by nelisabe          #+#    #+#             */
/*   Updated: 2020/11/13 19:26:08 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

/*
**	envp_delete_element delets given envp_element
*/

void	envp_delete_element(t_envp *envp_element, void (*delete)(void *))
{
	if (!(envp_element && delete))
		return ;
	delete(envp_element->variable);
	free(envp_element);
}

/*
**	envp_lst_clear deletes all envp list elements
*/

void	envp_lst_clear(t_envp **envp_list, void (*delete)(void*))
{
	t_envp *temp;

	if (!(envp_list && delete))
		return ;
	while (*envp_list)
	{
		temp = (*envp_list)->next;
		envp_delete_element(*envp_list, delete);
		*envp_list = temp;
	}
	*envp_list = NULL;
}
