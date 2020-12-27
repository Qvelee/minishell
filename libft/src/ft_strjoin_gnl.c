/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:32:53 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/27 10:49:26 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_strlen_2(const char *s)
{
	size_t len;

	len = 0;
	if (s)
		while (s[len])
			len++;
	return (len);
}

char		*join_free(char const *s1, char const *s2)
{
	char *out;
	char *head;
	char *copy1;

	copy1 = (char*)s1;
	if (!(out = (char*)malloc(ft_strlen_2(s1) + ft_strlen_2(s2) + 1)))
	{
		free(copy1);
		return (0);
	}
	head = out;
	while (s1 && *s1++)
		*out++ = *(s1 - 1);
	while (s2 && *s2++)
		*out++ = *(s2 - 1);
	free(copy1);
	*out = 0;
	return (head);
}
