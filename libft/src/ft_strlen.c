/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgertrud <msnazarow@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 02:41:59 by sgertrud          #+#    #+#             */
/*   Updated: 2020/12/20 04:45:13 by sgertrud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlen_term(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
	{
		if (s[len] < 0)
			s++;
		len++;
	}
	return (len);
}

int	ft_substrlen(char *start, char *end)
{
	int len;

	len = 0;
	while (start < end)
	{
		if (*start < 0)
				start++;
		len++;
		start++;
	}
	return(len);
}