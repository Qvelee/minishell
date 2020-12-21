/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 06:37:40 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/20 04:27:14 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_history(t_history *history)
{
	while(history->next)
	{
		history = history->next;
	}
	while(history->prev)
	{
		free(history->str);
		history = history->prev;
		free(history->next);
	}
	free(history->str);
	free(history);
}