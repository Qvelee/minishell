/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 06:37:40 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:24:07 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "stdlib.h"

void	free_history(t_history *history)
{
	if (history)
	{
		while (history->next)
		{
			history = history->next;
		}
		while (history->prev)
		{
			free(history->str);
			history->str = 0;
			history = history->prev;
			free(history->next);
			history->next = 0;
		}
		free(history->str);
		free(history);
	}
}
