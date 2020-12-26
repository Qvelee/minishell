/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 20:20:05 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/25 19:15:34 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

static void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char*)s++ = 0;
}

char		**ft_realloc(char **data, size_t len, size_t newlen)
{
	char **out;

	if (!(out = (char**)malloc(newlen * sizeof(char*))))
		return (0);
	ft_bzero(out, newlen * sizeof(char*));
	while (data && len--)
		out[len] = data[len];
	free(data);
	return (out);
}

char		*ft_realloc_str(char *data, size_t len, size_t newlen)
{
	char *out;

	if (!(out = (char*)malloc(newlen * sizeof(char))))
		return (0);
	ft_bzero(out, newlen * sizeof(char));
	while (data && len--)
		out[len] = data[len];
	free(data);
	return (out);
}
