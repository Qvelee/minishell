/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 01:29:38 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/21 08:18:19 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

t_history *add_history(t_history *head, char *str)
{
	t_history *prev;

	if (head)
	{
		head->next = ft_calloc(sizeof(t_history),1);
		prev = head;
		head = head->next;
		head->str = str;
		head->prev = prev;
	}
	else
	{
		head = malloc(sizeof(t_history));
		head->prev = 0;
		head->next = 0;
		head->str = str;
	}

	return (head);
}

t_history *read_history(int fd)
{
	t_history *head;
	int ret;
	t_history *prev;
	t_history *next;
	char *str;
	head = ft_calloc(sizeof(t_history),1);
	head->prev = NULL;
	prev = head;
	str = 0;
	while ((ret = get_next_line(fd, &str)) >= 0)
	{
		if (!*str)
			free(str);
		else
		{
			head->str = str;
			head->next = ft_calloc(sizeof(t_history),1);
			prev = head;
			head = head->next;
			head->prev = prev;
		}
		if (ret == 0)
			break;
	}

	head = head->prev;
	free(head->next);
	head->next = 0;

	return(head);
}