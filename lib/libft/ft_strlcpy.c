/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:43:51 by eproust           #+#    #+#             */
/*   Updated: 2024/09/25 18:07:47 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < size)
		ft_memcpy(dst, src, src_len + 1);
	else if (size > 0)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (src_len);
}

/*
#include <stdio.h>
#include <bsd/string.h>

// size should be equal to strlen(dest)
int main (void)
{
	char	str[10] = "helloworld";
	char	dest[10]; ft_memset(dest, 'A', 10);
	char	dest1[10]; ft_memset(dest1, 'A', 10);

	size_t res = ft_strlcpy(dest, str, 0);
	printf("ft_strlcpy:	'%s' (return: %zu)\n", dest, res);

	size_t res1 = strlcpy(dest1, str, 0);
	printf("strlcpy:	'%s' (return: %zu)\n", dest1, res1);
}
*/
