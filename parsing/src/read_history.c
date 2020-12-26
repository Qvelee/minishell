/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 01:29:38 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/26 12:23:16 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "main.h"

t_history	*add_history(t_history *head, char *str)
{
	t_history *prev;

	if (head)
	{
		head->next = ft_calloc(sizeof(t_history), 1);
		prev = head;
		head = head->next;
		head->str = str;
		head->prev = prev;
		head->next = 0;
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

void		add_one_line(char *str, t_history **head)
{
	t_history	*prev;

	(*head)->str = str;
	(*head)->next = ft_calloc(sizeof(t_history), 1);
	prev = (*head);
	(*head) = (*head)->next;
	(*head)->prev = prev;
}

t_history	*read_history(int fd)
{
	t_history	*head;
	int			ret;
	char		*str;

	head = ft_calloc(sizeof(t_history), 1);
	head->prev = NULL;
	str = 0;
	while ((ret = get_next_line(fd, &str)) >= 0)
	{
		if (!*str)
			free(str);
		else
			add_one_line(str, &head);
		if (ret == 0)
			break ;
	}
	if (head->prev)
	{
		head = head->prev;
		free(head->next);
		head->next = 0;
	}
	return (head);
}
