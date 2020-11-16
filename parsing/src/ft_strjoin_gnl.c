/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:32:53 by sgertrud          #+#    #+#             */
/*   Updated: 2020/11/13 20:33:01 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_strlen_gnl(const char *s)
{
	size_t len;

	len = 0;
	if (s)
		while (s[len])
			len++;
	return (len);
}

char		*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char *out;
	char *head;
	char *copy1;

	copy1 = (char*)s1;
	if (!(out = (char*)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1)))
		return (0);
	head = out;
	while (s1 && *s1++)
		*out++ = *(s1 - 1);
	while (s2 && *s2++)
		*out++ = *(s2 - 1);
	free(copy1);
	*out = 0;
	return (head);
}
